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


#ifndef SHEET_H
#define SHEET_H

#include <QtCore/QAbstractItemModel>

#include "commons.h"
#include "Column.h"
#include "AsocData.h"
#include "BasicColumns.h"

struct ICellObserver
{
  virtual ~ICellObserver() {}

  virtual void update(int row, int col) = 0;
};

struct Sheet
{
  enum enMode {editMode, printMode}; //different columns set available when printing!

  Sheet(const SheetData& data, ICellObserver* obs = NULL);

  //TODO: load/save support
  void load(const SheetData& data);
  SheetData save() const;

  void insertRow(const RowId& newRowId = RowId(), const RowId& rowId = RowId());
  void deleteRow(const RowId& rowId);
  void insertColumn(Column* newCol, const ColId& colId = ColId());
  void deleteColumn(const ColId& colId);

  int rowCount() const;
  int columnCount() const;

  const RowId * rowAt(int index) const;
  const Column* columnAt(int index) const;
  ICell* cellAt(int row, int column) const;

  numeric_t totalRowValue(const RowId& rowId) const;

  void update(const RowId & rowId, const ColId & colId) const;

  Column* createColumn(const ColumnData &col, const SheetData &data);

  const InputColumn* findInput(const QString & colTitle) const;
private:
  int findRow(const RowId& rowId) const;
  int findCol(const ColId& colId) const;

private:
  enMode m_mode;
  QList<RowId> m_rows;
  QList<Column*> m_columns;
  ICellObserver* m_pObserver;
};

struct SheetModel : public QAbstractTableModel
                  , public ICellObserver
{
  SheetModel(SheetData& s, QObject* parent = NULL);

  //implement ICellObserver
  virtual void update(int row, int col);

  //implement QAbstractTableModel
protected:
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
  virtual QVariant data(const QModelIndex &index, int role) const;
  virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
  //virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
  //virtual QModelIndex parent(const QModelIndex &index) const;
private:
  Sheet m_sheet;
};

#endif // SHEET_H
