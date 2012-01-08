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



#include "Column.h"
#include "Cell.h"
#include "Sheet.h"

Column::Column(const Sheet& sheet, const ColId & colId /*= ColId()*/, const QString & title /*= QString()*/)
  : m_sheet(sheet)
  , m_colId(colId.isNull() ? ColId(QUuid::createUuid()) : colId)
  , m_title(title)
{
}

double Column::getTotalData() const
{
  double total = 0.0;

  ICell* pCell = NULL;
  foreach(pCell, m_cells)
    total += pCell->getData().toDouble();

  return total;
}

double Column::getTotalValue(const OutputColumn* pColumn) const
{
  double total = 0.0;

  ICell* pCell = NULL;
  foreach(pCell, m_cells)
    total += pCell->getValue(pColumn);

  return total;
}

ICell* Column::cellAt(int row) const
{
  if (0 <= row && row < m_cells.size())
    return m_cells[row];

  return NULL;
}

ICell* Column::cellAt(const RowId & rowId) const
{
  int row = findRow(rowId);
  if (row >= 0)
    return m_cells[row];

  return NULL;
}

void Column::insertRow(const RowId& newRowId, int index)
{
  ICell* pNewCell = createCell(newRowId, index);

  m_cells.insert(m_cells.begin()+index, pNewCell);
}

void Column::deleteRow(int index)
{
  m_cells.erase(m_cells.begin()+index);
}

void Column::addObserver(Column* pColumn)
{
  m_observers.push_back(pColumn);
}

void Column::removeObserver(Column* pColumn)
{
  int index = m_observers.indexOf(pColumn);

  if (index >= 0)
    m_observers.erase(m_observers.begin()+index);
}

void Column::notify(const RowId & rowChanged) const
{
  Column* pColumn = NULL;
  foreach(pColumn, m_observers)
    pColumn->update(rowChanged);
}

void Column::update(const RowId & rowChanged) const
{
  m_sheet.update(rowChanged, m_colId);
}

int Column::findRow(const RowId& rowId) const
{
  int row = -1;

  ICell* pCell = NULL;
  foreach(pCell, m_cells)
  {
    ++row;
    if (pCell && pCell->rowId() == rowId)
      return row;
  }

  return -1;
}


void Column::createCells()
{
  Q_ASSERT(m_cells.size() == 0);

  //resize according to current sheet size
  const int nRows = m_sheet.rowCount();

  for(int i = 0; i < nRows; ++i)
  {
    const RowId * pRowId = m_sheet.rowAt(i);
    Q_ASSERT(pRowId);
    if (pRowId)
    {
      ICell* pNewCell = createCell(*pRowId, i);

      m_cells.push_back(pNewCell);
    }
  }

  Q_ASSERT(m_cells.size() == nRows);
}



/**
 * base class for all inputs/coefficients columns
 */
InputColumn::InputColumn(const Sheet& sheet, const ColId & colId, const QString & title)
  : Column(sheet, colId, title)
{
}

numeric_t InputColumn::getInputValue(const numeric_t & referenceValue, const OutputColumn * pColumn, const RowId & forRow) const
{
  numeric_t value = referenceValue;

  if (pColumn)
  {
    //TODO: search in custom values
  }

  return value;
}

void InputColumn::setCustomInputValue(const OutputColumn * pColumn, const RowId & forRow)
{
  //store a map of custom values (per row, per output column)
}




/**
 * base class for all outputs/amounts columns
 */
OutputColumn::OutputColumn(const Sheet& sheet, const ColId & colId, const QString & title)
  : Column(sheet, colId, title)
{
}





struct CompositeCell : public ICell
{
  CompositeCell(const Column& col, const RowId& rowId) : ICell(col, rowId) {}

  virtual bool isEditable() const {return false;}
  virtual bool isNumeric() const {return true;}
  virtual void setData(const variant_t & /*v*/) { Q_ASSERT(false); }
  virtual variant_t getData() const { Q_ASSERT(false); return getValue(NULL);}

  virtual bool isPartOfTotal() const {return false;}
  virtual numeric_t getValue(const OutputColumn* pColumn) const {return m_value;}

  //TODO: observe childs/components and auto-recompute m_value as total of childs values
private:
  numeric_t m_value;
};

/**
 * composite column (auto sums child columns)
 */
CompositeColumn::CompositeColumn(const Sheet &sheet, const ColId &colId, const QString &title)
  : Column(sheet, colId, title)
{
}

CompositeColumn::~CompositeColumn()
{
  Column* pComponent = NULL;
  foreach(pComponent, m_components)
    delete pComponent;
}

void CompositeColumn::addComponent(Column *pComponent)
{
  m_components.push_back(pComponent);
}

ICell *CompositeColumn::createCell(const RowId &rowId, int index) const
{
  return new CompositeCell(*this, rowId);
}
