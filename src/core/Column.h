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
  virtual ~Column();

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

  void addComponent(Column* pComponent) const; //allow 'composite' columns

protected:
  const Sheet& m_sheet;
  const ColId m_colId;
  QString m_title;
  QList<ICell*> m_cells;
  QList<Column*> m_observers;
  mutable QList<Column*> m_components;
};

#endif // COLUMN_H
