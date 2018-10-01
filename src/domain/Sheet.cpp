/*
 * Copyright (c) 2018, Kware, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from Kware,
 * or a written licence from an organisation licenced by Kware
 * to grant such a licence.
 */

#include "domain/Sheet.h"
#include "domain/Cell.h"

#include "domain/BasicColumns.h"
#include "domain/InputDivColumn.h"
#include "domain/InputCntColumn.h"
#include "domain/OutputAutoSumColumn.h"
#include "domain/OutputAutoSplitColumn.h"
#include "domain/Invoice.h"

#include <QtGui/QBrush>
#include <QtGui/QColor>
#include <QtGui/QFont>


/*
 * main bzl class
 */
Sheet::Sheet(const SheetData& data, ICellObserver* obs /* = nullptr */)
  : m_mode(editMode)
  , m_pObserver(obs)
{
  load(data);
}

void Sheet::load(const SheetData& data)
{
  m_rows.clear();
  m_columns.clear();


  /* 1. add rows */
  foreach(const LodgerData & lodg, data.lodgers)
  {
    insertRow(lodg.id);
  }


  /* 2. add input columns */
  //StringColumn* pNamesCol = new StringColumn(*this, ColId(), "nume");
  //insertColumn(pNamesCol); //special column: name always comes first

  foreach(const ColumnData & col, data.columns)
  {
    if (col.type.startsWith("input."))
    {
      createColumn(col, data);
    }
  }

  /* 3. fill inputs: names... */
  int l = 0; //rows
  foreach(const LodgerData & lodg, data.lodgers)
  {
    //pNamesCol->cellAt(l)->setData(lodg.name);

    //inputs:
    for(int c = 0, n = m_columns.size(); c<n; ++c)
    {
      StringColumn* pInputTextColumn = dynamic_cast<StringColumn*>(m_columns[c]);
      if (pInputTextColumn)
      {
        const QString & val = lodg.inputText[pInputTextColumn->getTitle()];

        pInputTextColumn->cellAt(l)->setData(val);

        continue;
      }

      InputColumn* pInputCol = dynamic_cast<InputColumn*>(m_columns[c]);
      if (pInputCol)
      {
        const numeric_t & val = lodg.inputValues[pInputCol->getTitle()];

        pInputCol->cellAt(l)->setData(val);
      }
    }

    ++l;
  }

  /* 4. add output columns */
  foreach(const ColumnData & col, data.columns)
  {
    if (col.type.startsWith("output."))
    {
      createColumn(col, data);
    }
  }

  insertColumn(new TotalColumn(*this, ColId(), "TOTAL")); //special column: total always comes last

  /* 5. customize inputs */
  //see InputColumn::setCustomInputValue
}

SheetData Sheet::save() const
{
  SheetData data;

  //TODO

  return data;
}

void Sheet::insertRow(const RowId& newRowId /*= RowId()*/, const RowId& rowId /*= RowId()*/)
{
  const RowId theIdForTheNewRow = newRowId.isNull() ? RowId(QUuid::createUuid()) : newRowId;
  Q_ASSERT(!theIdForTheNewRow.isNull());

  const int index = rowId == RowId() ? m_rows.size() : findRow(rowId);
  Q_ASSERT(index >= 0);

  if (index >= 0)
  {
    m_rows.insert(index, theIdForTheNewRow);

    //initialize row
    Column* pColumn = nullptr;
    foreach(pColumn, m_columns)
      pColumn->insertRow(theIdForTheNewRow, index);
  }
}

void Sheet::deleteRow(const RowId& rowId)
{
  const int index = findRow(rowId);

  Q_ASSERT(index >= 0);

  if (index >= 0)
  {
    m_rows.erase(m_rows.begin() + index);

    //destroy row
    Column* pColumn = nullptr;
    foreach(pColumn, m_columns)
      pColumn->deleteRow(index);
  }
}

void Sheet::insertColumn(Column* newCol, const ColId& colId /*= ColId()*/)
{
  Q_ASSERT(newCol && !newCol->id().isNull());

  const int index = colId == ColId() ? m_columns.size() : findCol(colId);
  Q_ASSERT(index >= 0);

  if (index >= 0)
  {
    newCol->createCells(); //initialize column

    m_columns.insert(index, newCol);
  }
}

void Sheet::deleteColumn(const ColId& colId)
{
  const int index = findCol(colId);

  Q_ASSERT(index >= 0);

  if (index >= 0)
  {
    delete m_columns[index]; //destroy column

    m_columns.erase(m_columns.begin() + index);
  }
}

numeric_t Sheet::totalRowValue(const RowId& rowId) const
{
  numeric_t rowTotal = 0.0;

  Column* pColumn = nullptr;
  foreach(pColumn, m_columns)
  {
    ICell* pCell = pColumn->cellAt(rowId);
    if (pCell && pCell->isNumeric() && pCell->isPartOfTotal())
      rowTotal += pCell->getValue(nullptr); //pass here the total column? useless
  }

  return rowTotal;
}

QString Sheet::totalRowDescription(const RowId& rowId) const
{
  QStringList rowAmounts;

  Column* pColumn = nullptr;
  foreach(pColumn, m_columns)
  {
    ICell* pCell = pColumn->cellAt(rowId);
    if (pCell && pCell->isNumeric() && pCell->isPartOfTotal())
      rowAmounts.append(QString("%1").arg(pCell->getDescription(nullptr))); //pass here the total column? useless
  }

  return rowAmounts.join(" + ");
}

void Sheet::update(const RowId & rowId, const ColId & colId) const
{
  if (m_pObserver)
  {
    const int rowIndex = findRow(rowId);
    const int colIndex = findCol(colId);

    m_pObserver->update(rowIndex, colIndex);
  }
}

void Sheet::createColumn(const ColumnData &col, const SheetData &data)
{
  const QString & title = col.name;
  const QString & type = col.type;

  if (type == "input.text")
  {
    insertColumn(new StringColumn(*this, col.id, title));
  }
  else if (type == "input.divider")
  {
    insertColumn(new InputDivColumn(*this, col.id, title));
  }
  else if (type == "input.counter")
  {
    insertColumn(new InputCntColumn(*this, col.id, title));
  }
  else if (type == "output.manual")
  {
    insertColumn(new OutputAutoSumColumn(*this, col.id, title));
  }
  else if (type == "output.autosplit")
  {
    OutputAutoSplitColumn* pCol = new OutputAutoSplitColumn(*this, col.id, title);

    //TODO: configure splits
    if (!col.commonsBy.empty())
    {
      SplitCommonsComponent* commons = new SplitCommonsComponent(*this, *pCol);
      foreach(const QString & title, col.commonsBy)
        commons->addInputColumn(findInput(title));
      commons->setPercent(col.commonsPercent);
    }

    if (!col.countedBy.empty())
    {
      SplitCountedComponent* counted = new SplitCountedComponent(*this, *pCol);
      foreach(const QString & title, col.countedBy)
        counted->addInputColumn(findInput(title));
      counted->setCountedUnits(col.countedUnits);
    }

    if (!col.dividedBy.empty())
    {
      SplitDividedComponent* divided = new SplitDividedComponent(*this, *pCol);
      foreach(const QString & title, col.dividedBy)
        divided->addInputColumn(findInput(title));
    }

    insertColumn(pCol);

    foreach(QString inv, col.invoices)
    {
      numeric_t amount = data.invoices[inv];

      pCol->addInvoice(new Invoice(amount, inv)); //TODO: ref invoices
    }

    pCol->splitAmount();
  }
  else
  {
    Q_ASSERT(false);
  }
}

const InputColumn *Sheet::findInput(const QString & colTitle) const
{
  const Column* pColumn = nullptr;
  foreach(pColumn, m_columns)
    if (pColumn->getTitle() == colTitle)
      break;

  Q_ASSERT(pColumn);

  return dynamic_cast<const InputColumn*>(pColumn);
}


int Sheet::findRow(const RowId& rowId) const
{
  return m_rows.indexOf(rowId);
}

int Sheet::findCol(const ColId& colId) const
{
  int index = -1;

  Column* pColumn = nullptr;
  foreach(pColumn, m_columns)
  {
    ++index;
    if (pColumn && pColumn->id() == colId)
      return index;
  }

  Q_ASSERT(false);
  return -1;
}

int Sheet::rowCount() const
{
  return m_rows.size();
}

int Sheet::columnCount() const
{
  //TODO
  //consider composites here! (they can be further expanded into their components)
  //consider required inputs sets (by auto-output columns)
  return m_columns.size();
}


const RowId * Sheet::rowAt(int index) const
{
  if (0 <= index && index < rowCount())
    return &m_rows[index];

  Q_ASSERT(false);
  return nullptr;
}

const Column* Sheet::columnAt(int index) const
{
  if (0 <= index && index < columnCount())
    return m_columns[index];

  Q_ASSERT(false);
  return nullptr;
}

ICell* Sheet::cellAt(int row, int column) const
{
  const Column* pColumn = columnAt(column);
  if (pColumn)
    return pColumn->cellAt(row);

  Q_ASSERT(false);
  return nullptr;
}
