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



#include "core/Sheet.h"
#include "core/Cell.h"

#include "core/BasicColumns.h"
#include "core/InputDivColumn.h"
#include "core/InputCntColumn.h"
#include "core/OutputAutoSumColumn.h"
#include "core/OutputAutoSplitColumn.h"
#include "core/Invoice.h"

/*
 * main bzl class
 */
Sheet::Sheet(const SheetData& data, ICellObserver* obs /*= NULL*/)
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
  StringColumn* pNamesCol = new StringColumn(*this, ColId(), "nume");
  insertColumn(pNamesCol); //special column: name always comes first

  foreach(const ColumnData & col, data.columns)
  {
    if (col.type.startsWith("input."))
    {
      Column* pCol = createColumn(col, data);
      insertColumn(pCol);
    }
  }

//  InputDivColumn* pPers = new InputDivColumn(*this, ColId(), "p");
//  insertColumn(pPers);

//  InputCntColumn* pCnt1 = new InputCntColumn(*this, ColId(), "ac1");
//  insertColumn(pCnt1);

//  InputCntColumn* pCnt2 = new InputCntColumn(*this, ColId(), "ac2");
//  insertColumn(pCnt2);

//  InputColumn* pAC = new InputColumn(*this, ColId(), "ac"); //composite: sum of ac1 and ac2
//  pAC->addComponent(pCnt1);
//  pAC->addComponent(pCnt2);
//  insertColumn(pAC);

  /* 3. fill inputs: names... */
  int l = 0; //rows
  foreach(const LodgerData & lodg, data.lodgers)
  {
    pNamesCol->cellAt(l)->setData(lodg.name);

    //input values:
    for(int c = 1, n = m_columns.size(); c<n; ++c)
    {
      InputColumn* pInputCol = dynamic_cast<InputColumn*>(m_columns[c]);
      if (pInputCol)
      {
        const numeric_t & val = lodg.inputValues[pInputCol->getTitle()];

        pInputCol->cellAt(l)->setData(val);
      }
    }
//    pPers->cellAt(l)->setData(lodg.inputValues[pPers->getTitle()]);
//    pCnt1->cellAt(l)->setData(lodg.inputValues[pCnt1->getTitle()]);
//    pCnt2->cellAt(l)->setData(lodg.inputValues[pCnt2->getTitle()]);

    ++l;
  }

  /* 4. add output columns */
  foreach(const ColumnData & col, data.columns)
  {
    if (col.type.startsWith("output."))
    {
      Column* pCol = createColumn(col, data);
      insertColumn(pCol);
    }
  }

//  insertColumn(new OutputAutoSumColumn(*this, ColId(), "restante"));

//  OutputAutoSplitColumn* pCol = new OutputAutoSplitColumn(*this, ColId(), "salubr");
//  SplitCommonsComponent* commons = new SplitCommonsComponent(*this, *pCol);
//  commons->addInputColumn(pPers);
//  commons->setPercent(15);
//  SplitCountedComponent* counted = new SplitCountedComponent(*this, *pCol);
//  counted->addInputColumn(pCnt1);
//  counted->setCountedUnits(48);
//  SplitDividedComponent* divided = new SplitDividedComponent(*this, *pCol);
//  divided->addInputColumn(pNamesCol); //equal
//  insertColumn(pCol);
//  pCol->addInvoice(new Invoice(352.46, "retim"));
//  pCol->splitAmount();

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
    Column* pColumn = NULL;
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
    Column* pColumn = NULL;
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

  Column* pColumn = NULL;
  foreach(pColumn, m_columns)
  {
    ICell* pCell = pColumn->cellAt(rowId);
    if (pCell && pCell->isNumeric() && pCell->isPartOfTotal())
      rowTotal += pCell->getValue(NULL); //pass here the total column? useless
  }

  return rowTotal;
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

Column *Sheet::createColumn(const ColumnData &col, const SheetData &data)
{
  const QString & title = col.name;
  const QString & type = col.type;

  if (type == "input.divider")
  {
    return new InputDivColumn(*this, col.id, title);
  }
  if (type == "input.counter")
  {
    return new InputCntColumn(*this, col.id, title);
  }
  if (type == "output.manual")
  {
    return new OutputAutoSumColumn(*this, col.id, title);
  }
  if (type == "output.autosplit")
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
    return pCol;
  }

  Q_ASSERT(false);
  return NULL;
}

const InputColumn *Sheet::findInput(const QString & colTitle) const
{
  const Column* pColumn = NULL;
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

  Column* pColumn = NULL;
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
  return NULL;
}

const Column* Sheet::columnAt(int index) const
{
  if (0 <= index && index < columnCount())
    return m_columns[index];

  Q_ASSERT(false);
  return NULL;
}

ICell* Sheet::cellAt(int row, int column) const
{
  const Column* pColumn = columnAt(column);
  if (pColumn)
    return pColumn->cellAt(row);

  Q_ASSERT(false);
  return NULL;
}









/*
 * qt model used to be attached to our tableview
 */
SheetModel::SheetModel(SheetData& s, QObject* parent /*= NULL*/)
  : QAbstractTableModel(parent)
  , m_sheet(s, this)
{
}

void SheetModel::update(int row, int col)
{
  //refresh cell in our views
  const QModelIndex modelIndex = createIndex(row, col, 0);

  emit dataChanged(modelIndex, modelIndex);
}

int SheetModel::rowCount(const QModelIndex &parent) const
{
  return m_sheet.rowCount();
}

int SheetModel::columnCount(const QModelIndex &parent) const
{
  return m_sheet.columnCount();
}

Qt::ItemFlags SheetModel::flags(const QModelIndex &index) const
{
  Qt::ItemFlags f = QAbstractItemModel::flags(index);

  const ICell* pCell = m_sheet.cellAt(index.row(), index.column());
  if (pCell && pCell->isEditable())
    f |= Qt::ItemIsEditable;

  return f;
}

QVariant SheetModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
  {
    if (0 <= section && section < m_sheet.columnCount())
    {
      const Column* pColumn = m_sheet.columnAt(section);
      if (pColumn)
        return pColumn->getTitle();
    }
  }

  return QVariant();
}

QVariant SheetModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  const ICell* pCell = m_sheet.cellAt(index.row(), index.column());
  Q_ASSERT(pCell);

  if (role == Qt::DisplayRole || role == Qt::ToolTipRole)
  {
    return pCell->isNumeric() ? pCell->getValue(NULL) : pCell->getData(); //TODO
  }
  else if (role == Qt::EditRole)
  {
    return pCell->getData();
  }

  return QVariant();
}

bool SheetModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (!index.isValid())
    return false;

  if (role == Qt::EditRole)
  {
    ICell* pCell = m_sheet.cellAt(index.row(), index.column());
    if (pCell /*&& pCell->isEditable()*/)
    {
      Q_ASSERT(pCell->isEditable());
      pCell->setData(value);
    }

    emit dataChanged(index, index);

    if (pCell->isPartOfTotal())
    {
      QModelIndex totalCellIndex = createIndex(index.row(), m_sheet.columnCount()-1, 0);//'total' should be the last column
      emit dataChanged(totalCellIndex, totalCellIndex);
    }

    return true;
  }

  return false;
}
