/*
 * Copyright (c) 2018, Kware, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from Kware,
 * or a written licence from an organisation licenced by Kware
 * to grant such a licence.
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
  virtual ~ICellObserver() = default;

  virtual void update(int row, int col) = 0;
};

struct Sheet
{
  enum enMode {editMode, printMode}; //different columns set available when printing!

  Sheet(ICellObserver* obs = nullptr);

  //TODO: load/save support
  void load(const SheetData& data);
  SheetData save() const;

private:
  void insertRow(const RowId& newRowId = RowId(), const RowId& rowId = RowId());
  void deleteRow(const RowId& rowId);
  void insertColumn(Column* newCol, const ColId& colId = ColId());
  void deleteColumn(const ColId& colId);

public:
  int rowCount() const;
  int columnCount() const;

  const RowId * rowAt(int index) const;
  const Column* columnAt(int index) const;
  ICell* cellAt(int row, int column) const;

  numeric_t totalRowValue(const RowId& rowId) const;
  QString totalRowDescription(const RowId& rowId) const;

  void update(const RowId & rowId, const ColId & colId) const;

  void createColumn(const ColumnData &col, const SheetData &data);

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

#endif // SHEET_H
