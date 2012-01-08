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

Column::~Column()
{
  Column* pComponent = NULL;
  foreach(pComponent, m_components)
    delete pComponent;
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

void Column::addComponent(Column *pComponent) const
{
  m_components.push_back(pComponent);
}

numeric_t Column::sumComponents(const RowId &rowId, const OutputColumn* pOutput) const
{
  numeric_t val = 0.0;

  foreach(Column* pComponent, m_components)
  {
    val += pComponent->cellAt(rowId)->getValue(pOutput);
  }

  return val;
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
