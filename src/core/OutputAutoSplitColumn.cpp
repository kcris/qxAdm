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


static const QString SplitCommons = "commons";
static const QString SplitCounted = "counted";
static const QString SplitDivided = "divided";


struct AutomaticCell : public ICell
{
  AutomaticCell(const SplitComponent& col, const RowId& rowId) : ICell(col, rowId) {}

  virtual bool isEditable() const {return false;}
  virtual bool isNumeric() const {return true;}
  virtual void setData(const variant_t & /*v*/) { Q_ASSERT(false); }
  virtual variant_t getData() const { Q_ASSERT(false); return getValue(); }

  virtual bool isPartOfTotal() const {return true;}
  virtual numeric_t getValue() const
  {
    const SplitComponent& col = static_cast<const SplitComponent&>(m_column);

    return col.getRowInputUnits(m_rowId) * col.getUnitPrice();
  }
};


/**
 * struct SplitComponent
 */
SplitComponent::SplitComponent(const Sheet& sheet, const QString & title, const OutputAutoSplitColumn & ownerCol)
  : OutputColumn(sheet, ColId(QUuid(QString("%1.%2").arg(ownerCol.id()).arg(title))), title)
  , m_amount(0.0)
  , m_pricePerUnit(0.0)
  , m_ownerCol(ownerCol)
{
}

variant_t SplitComponent::getDescription() const
{
  return QString("%1: amount=%2 units=%3 price=%4")
      .arg(getTitle())
      .arg(getAmount())
      .arg(getInputsUnitsTotal())
      .arg(m_pricePerUnit);
}

numeric_t SplitComponent::getCellValue(const ICell & cell, const numeric_t & value) const
{
  //
  //1 - handle custom inputs
  //
  //TODO move here code from InputColumn::getInputValue, InputColumn::setCustomInputValue


  //
  //2 - handle implicit inter-split dependencies:
  //

  //if 'counted' is null, don't consider 'divided'
  if (getTitle() == SplitDivided)
  {
    SplitComponent* pSplitCounted = m_ownerCol.getSplitComponent(SplitCounted);
    if (pSplitCounted)
      if (!pSplitCounted->getRowInputUnits(cell.rowId()))
        return 0;
  }

  return value;
}

void SplitComponent::addInputColumn(const InputColumn* pInputCol)
{
  m_inputs.push_back(pInputCol);
  const_cast<InputColumn*>(pInputCol)->addObserver(this); //obs array should be mutable?
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

  const InputColumn* pInputCol = NULL;
  foreach(pInputCol, m_inputs)
    totalInputsUnits += pInputCol->getTotalValue(this);

  return totalInputsUnits;
}

numeric_t SplitComponent::getRowInputUnits(const RowId& rowId) const
{
  numeric_t units = 0.0;


  const InputColumn* pInputCol = NULL;
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
  : SplitComponent(sheet, SplitCommons, ownerCol)
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
  : SplitComponent(sheet, SplitCounted, ownerCol)
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
  : SplitComponent(sheet, SplitDivided, ownerCol)
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
  virtual variant_t getData() const { Q_ASSERT(false); return getValue(); }

  virtual bool isPartOfTotal() const {return true;}
  virtual numeric_t getValue() const
  {
    const OutputAutoSplitColumn& col = static_cast<const OutputAutoSplitColumn&>(m_column);

    numeric_t val = 0.0;

    foreach(const Column* pComponent, col.components())
    {
      const SplitComponent* pSplit = dynamic_cast<const SplitComponent*>(pComponent);
      Q_ASSERT(pSplit);
      val += pSplit->cellAt(m_rowId)->getValue(pSplit);
    }

    return val;

    //return static_cast<const OutputAutoSplitColumn&>(m_column).sumComponents(m_rowId, pOutputCol);
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

variant_t OutputAutoSplitColumn::getDescription() const
{
  QStringList desc;
  foreach(const Column* pComponent, m_components)
    desc << pComponent->getDescription().toString();

  return desc.join("\n");
}

void OutputAutoSplitColumn::addInvoice(Invoice* pInvoice)
{
  m_invoices.push_back(pInvoice);
}

void OutputAutoSplitColumn::addSplitComponent(SplitComponent* pComponent) const
{
  Column::addComponent(pComponent);
}

SplitComponent* OutputAutoSplitColumn::getSplitComponent(const QString & title) const
{
  foreach(Column* pComponent, m_components)
  {
    SplitComponent* pSplit = dynamic_cast<SplitComponent*>(pComponent);
    Q_ASSERT(pSplit);
    if (pSplit->getTitle() == title)
      return pSplit;
  }

  return NULL;
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

  Q_ASSERT(compareNumeric(getTotalValue(NULL/*this*/), getAmount())); //cells sum should match
}
