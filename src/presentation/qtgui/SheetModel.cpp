/*
 * Copyright (c) 2018, Kware, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from Kware,
 * or a written licence from an organisation licenced by Kware
 * to grant such a licence.
 */

#include "presentation/qtgui/SheetModel.h"
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
 * qt model used to be attached to our tableview
 */
SheetModel::SheetModel(SheetData& s, QObject* parent /* = nullptr */)
  : QAbstractTableModel(parent)
  , m_sheet(s, this)
{
}

void SheetModel::update(int row, int col)
{
  //refresh cell in our views
  const QModelIndex modelIndex = createIndex(row, col, nullptr);

  emit dataChanged(modelIndex, modelIndex);
}

int SheetModel::rowCount(const QModelIndex &/*parent*/) const
{
  return m_sheet.rowCount() + 1; //last one is TOTAL row
}

int SheetModel::columnCount(const QModelIndex &/*parent*/) const
{
  return m_sheet.columnCount();
}

Qt::ItemFlags SheetModel::flags(const QModelIndex &index) const
{
  Qt::ItemFlags f = QAbstractItemModel::flags(index);

  if (index.row() < m_sheet.rowCount()) //exclude TOTAL row
  {
    const ICell* pCell = m_sheet.cellAt(index.row(), index.column());
    if (pCell && pCell->isEditable())
      f |= Qt::ItemIsEditable;
  }

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

  const bool isTotalRow = !(index.row() < m_sheet.rowCount());

  if (role == Qt::FontRole)
  {
    QFont font;
    font.setBold(isTotalRow);
    return font;
  }

  if (role != Qt::DisplayRole && role != Qt::ToolTipRole && role != Qt::BackgroundRole && role != Qt::ForegroundRole && role != Qt::EditRole)
    return QVariant();

  if (!isTotalRow)
  {
    const ICell* pCell = m_sheet.cellAt(index.row(), index.column());
    Q_ASSERT(pCell);

    if (role == Qt::DisplayRole)
    {
      return pCell->isNumeric() ? pCell->getValue(nullptr) : pCell->getData(); //TODO
    }
    if (role == Qt::ToolTipRole)
    {
      return pCell->getDescription(nullptr); //TODO
    }
    else if (role == Qt::BackgroundRole)
    {
      if (pCell->isEditable())
        return QBrush(QColor(0xFF, 0xFF, 0xE0)); //custom bg for editable cells
    }
    else if (role == Qt::ForegroundRole)
    {
      if (pCell->isEditable())
        return QBrush(Qt::black); //custom fg for editable cells
    }
    else if (role == Qt::EditRole)
    {
      return pCell->getData();
    }
  }
  else //TOTAL row (summary)
  {
    const Column* pColumn = m_sheet.columnAt(index.column());
    if (pColumn)
    {
      if (role == Qt::DisplayRole)
        return pColumn->getSummary();

      if (role == Qt::ToolTipRole)
        return pColumn->getDescription();
    }
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
      QModelIndex totalCellIndex = createIndex(index.row(), m_sheet.columnCount()-1, nullptr);//'total' should be the last column
      emit dataChanged(totalCellIndex, totalCellIndex);
    }

    return true;
  }

  return false;
}
