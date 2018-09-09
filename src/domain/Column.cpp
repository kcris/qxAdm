/*
 * Copyright (c) 2018, Kware, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from Kware,
 * or a written licence from an organisation licenced by Kware
 * to grant such a licence.
 */

#include "domain/Column.h"
#include "domain/Cell.h"
#include "domain/Sheet.h"

Column::Column(const Sheet& sheet, const ColId & colId /*= ColId()*/, const QString & title /*= QString()*/)
  : m_sheet(sheet)
  , m_colId(colId.isNull() ? ColId(QUuid::createUuid()) : colId)
  , m_title(title)
{
}

Column::~Column()
{
  Column* pComponent = nullptr;
  foreach(pComponent, m_components)
    delete pComponent;
}

numeric_t Column::getTotalData() const
{
  numeric_t total = 0.0;

  ICell* pCell = nullptr;
  foreach(pCell, m_cells)
    total += pCell->getData().toDouble();

  return total;
}

numeric_t Column::getTotalValue(const CellValueRetriever* pColumn) const
{
  numeric_t total = 0.0;

  ICell* pCell = nullptr;
  foreach(pCell, m_cells)
    total += pCell->getValue(pColumn);

  return total;
}

ICell* Column::cellAt(int row) const
{
  if (0 <= row && row < m_cells.size())
    return m_cells[row];

  return nullptr;
}

ICell* Column::cellAt(const RowId & rowId) const
{
  int row = findRow(rowId);
  if (row >= 0)
    return m_cells[row];

  return nullptr;
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
  Column* pColumn = nullptr;
  foreach(pColumn, m_observers)
    pColumn->update(rowChanged);
}

void Column::update(const RowId & rowChanged) const
{
  m_sheet.update(rowChanged, m_colId);
}

variant_t Column::getSummary() const
{
  return getTotalValue(nullptr);
}

int Column::findRow(const RowId& rowId) const
{
  int row = -1;

  ICell* pCell = nullptr;
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

numeric_t Column::sumComponents(const RowId &rowId, const CellValueRetriever* pOutput) const
{
  numeric_t val{};

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
