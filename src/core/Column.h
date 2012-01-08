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


#ifndef COLUMN_H
#define COLUMN_H

#include "commons.h"

class ICell;
struct Sheet;
struct OutputColumn;

struct Column
{
  Column(const Sheet& sheet, const ColId & colId = ColId(), const QString & title = QString());
  virtual ~Column() {}

  const ColId & id() const {return m_colId;}
  const Sheet & sheet() const {return m_sheet;}

  int rowCount() const {return m_cells.size();}

  const QString & getTitle() const {return m_title;}

  numeric_t getTotalData() const;
  numeric_t getTotalValue(const OutputColumn*) const;

  ICell* cellAt(int row) const;
  ICell* cellAt(const RowId & rowId) const;

  void insertRow(const RowId& newRowId, int index);
  void deleteRow(int index);

  void createCells();

  void addObserver(Column*);
  void removeObserver(Column*);
  void notify(const RowId & rowChanged) const;
  virtual void update(const RowId & rowChanged) const; //override this to react as observer

protected:
  virtual ICell* createCell(const RowId& rowId, int index) const = 0;

protected:
  int findRow(const RowId& rowId) const;

protected:
  const Sheet& m_sheet;
  const ColId m_colId;
  QString m_title;
  QList<ICell*> m_cells;
  QList<Column*> m_observers;
};


//looks like a hack, but...original input values can be customized/overridden with other values
//
//If you don't want to create additional columns, our solution is to allow an input cell to return a value other
//than the 'real' one when a specific output cell (row, column) asks for the input
struct InputColumn : public Column
{
  InputColumn(const Sheet& sheet, const ColId & colId, const QString & title);

  //get our input value: real or overridden (if present)
  numeric_t getInputValue(const numeric_t & referenceValue, const OutputColumn * pColumn, const RowId & forRow) const;

  //store a custom/overridden value for my input (we'll return that later, when a specific output cell wants our value)
  void setCustomInputValue(const OutputColumn * pColumn, const RowId & forRow);

private:
  //TODO: store array of custom values, for some outputcolumns
  //outputcolid,rowid -> numeric_t
};

struct OutputColumn : public Column
{
  OutputColumn(const Sheet& sheet, const ColId & colId, const QString & title);
};

//TODO: generic composite columns - e.g for compositing inputs (for outputs we already have CompositeAutoSplitOutputColumn)

struct CompositeColumn : public Column
{
  CompositeColumn(const Sheet& sheet, const ColId & colId, const QString & title);
  virtual ~CompositeColumn();

protected:
  virtual ICell* createCell(const RowId& rowId, int index) const;

protected:
  void addComponent(Column* pComponent);

protected:
  QList<Column*> m_components;
};

#endif // COLUMN_H
