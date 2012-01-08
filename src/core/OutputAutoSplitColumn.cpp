/*
 * Copyright (c) 2011, DidiSoft, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from DidiSoft,
 * or a written licence from an organisation licenced by DidiSoft
 * to grant such a licence.
 *
 * $Id:$
 * $Date:$
 * $Rev:$
 */



#include "OutputAutoSplitColumn.h"
#include "Invoice.h"
#include "Cell.h"
#include "Sheet.h"

struct AutomaticCell : public ICell
{
  AutomaticCell(const SplitComponent& col, const RowId& rowId) : ICell(col, rowId) {}

  virtual bool isEditable() const {return false;}
  virtual bool isNumeric() const {return true;}
  virtual void setData(const variant_t & /*v*/) { Q_ASSERT(false); }
  virtual variant_t getData() const { Q_ASSERT(false); return getValue(NULL); }

  virtual bool isPartOfTotal() const {return true;}
  virtual numeric_t getValue(const OutputColumn*) const
  {
    const SplitComponent& col = static_cast<const SplitComponent&>(m_column);

    return col.getRowInputUnits(m_rowId) * col.getUnitPrice();
  }
};


/**
 * struct SplitComponent
 */
SplitComponent::SplitComponent(const Sheet& sheet, const QString & suffix, const OutputAutoSplitColumn & ownerCol)
  : OutputColumn(sheet, ColId(QUuid(QString("%1.%2").arg(ownerCol.id()).arg(suffix))), suffix)
  , m_amount(0.0)
  , m_pricePerUnit(0.0)
  , m_ownerCol(ownerCol)
{
}

void SplitComponent::addInputColumn(InputColumn* pInputCol)
{
  m_inputs.push_back(pInputCol);
  pInputCol->addObserver(this);
}

ICell* SplitComponent::createCell(const RowId& rowId, int index) const
{
  return new AutomaticCell(*this, rowId);
}

numeric_t SplitComponent::getAmount() const
{
  return m_amount;
}

numeric_t SplitComponent::setAmount(const numeric_t & amount)
{
  doSetAmount(amount);

  m_pricePerUnit = getAmount() / getInputsUnitsTotal();

  //notify that our cells were 'recomputed'
  ICell* pCell = NULL;
  foreach(pCell, m_cells)
    pCell->notify();

  const numeric_t & myAmount = getAmount();
  Q_ASSERT(compareNumeric(getTotalValue(this), myAmount)); //cells sum should match
  return myAmount;
}

numeric_t SplitComponent::getInputsUnitsTotal() const
{
  numeric_t totalInputsUnits = 0.0;

  InputColumn* pInputCol = NULL;
  foreach(pInputCol, m_inputs)
    totalInputsUnits += pInputCol->getTotalValue(this);

  return totalInputsUnits;
}

numeric_t SplitComponent::getRowInputUnits(const RowId& rowId) const
{
  numeric_t units = 0.0;


  InputColumn* pInputCol = NULL;
  foreach(pInputCol, m_inputs)
  {
    ICell* pCell = pInputCol->cellAt(rowId);
    Q_ASSERT(pCell);
    if (pCell)
      units += pCell->getValue(this);
  }

  return units;
}

numeric_t SplitComponent::getUnitPrice() const
{
  return m_pricePerUnit;
}

void SplitComponent::update(const RowId & /*rowChanged*/) const
{
  m_pricePerUnit = getAmount() / getInputsUnitsTotal();

  //*all* cells have to be actually refreshed
  ICell* pCell = NULL;
  foreach(pCell, m_cells)
    m_sheet.update(pCell->rowId(), m_colId);
}




/**
 * struct SplitCommonsComponent
 */
SplitCommonsComponent::SplitCommonsComponent(const Sheet& sheet, const OutputAutoSplitColumn & ownerCol)
  : SplitComponent(sheet, "commons", ownerCol)
  , m_percent(0)
{
  ownerCol.addSplitComponent(this);
}

void SplitCommonsComponent::doSetAmount(const numeric_t & amount)
{
  if (m_percent == 0.0)
    return;
  Q_ASSERT(m_percent > 0.0 && !m_inputs.empty());

  //handle fraction of original amount
  m_amount = amount * m_percent / 100;
}



/**
 * struct SplitCountedComponent
 */
SplitCountedComponent::SplitCountedComponent(const Sheet& sheet, const OutputAutoSplitColumn & ownerCol)
  : SplitComponent(sheet, "counted", ownerCol)
  , m_countedUnits(0)
{
  ownerCol.addSplitComponent(this);
}

void SplitCountedComponent::doSetAmount(const numeric_t & amount)
{
  if (m_countedUnits == 0.0)
    return;

  const numeric_t totalInputsUnits = getInputsUnitsTotal();
  Q_ASSERT(totalInputsUnits > 0.0 && !m_inputs.empty());

  //handle fraction of original amount
  m_amount = amount / m_countedUnits * totalInputsUnits;
}



/**
 * struct SplitDividedComponent
 */
SplitDividedComponent::SplitDividedComponent(const Sheet& sheet, const OutputAutoSplitColumn & ownerCol)
  : SplitComponent(sheet, "divided", ownerCol)
{
  ownerCol.addSplitComponent(this);
}

void SplitDividedComponent::doSetAmount(const numeric_t & amount)
{
  Q_ASSERT(/*amount > 0.0 &&*/ !m_inputs.empty());

  //handle all original amount
  m_amount = amount;
}






struct OutputAutoSplitCell : public ICell
{
  OutputAutoSplitCell(const OutputAutoSplitColumn& col, const RowId& rowId) : ICell(col, rowId) {}

  virtual bool isEditable() const {return false;}
  virtual bool isNumeric() const {return true;}
  virtual void setData(const variant_t & /*v*/) { Q_ASSERT(false); }
  virtual variant_t getData() const { Q_ASSERT(false); return getValue(NULL); }

  virtual bool isPartOfTotal() const {return true;}
  virtual numeric_t getValue(const OutputColumn* pOutputCol) const
  {
    return static_cast<const OutputAutoSplitColumn&>(m_column).sumComponents(m_rowId, pOutputCol);
  }
};



/**
 * struct OutputAutoSplitColumn
 */
OutputAutoSplitColumn::OutputAutoSplitColumn(const Sheet& sheet, const ColId & colId, const QString & title)
  : OutputColumn(sheet, colId, title)
{
}

OutputAutoSplitColumn::~OutputAutoSplitColumn()
{
  Invoice* pInvoice = NULL;
  foreach(pInvoice, m_invoices)
    delete pInvoice;
}


void OutputAutoSplitColumn::addInvoice(Invoice* pInvoice)
{
  m_invoices.push_back(pInvoice);
}

void OutputAutoSplitColumn::addSplitComponent(SplitComponent* pComponent) const
{
  Column::addComponent(pComponent);
}

ICell *OutputAutoSplitColumn::createCell(const RowId &rowId, int index) const
{
  foreach(Column* pComponent, m_components)
    pComponent->insertRow(rowId, index);

  return new OutputAutoSplitCell(*this, rowId);
}

numeric_t OutputAutoSplitColumn::getAmount() const
{
  numeric_t amount = 0.0;

  Invoice* pInvoice = NULL;
  foreach(pInvoice, m_invoices)
    amount += pInvoice->m_amount;

  return amount;
}

void OutputAutoSplitColumn::splitAmount()
{
  numeric_t amount = getAmount();

  foreach(Column* pComponent, m_components)
  {
    SplitComponent* pSplit = dynamic_cast<SplitComponent*>(pComponent);
    amount -= pSplit->setAmount(amount);
  }

  Q_ASSERT(amount == 0.0);

  Q_ASSERT(compareNumeric(getTotalValue(this), getAmount())); //cells sum should match
}
