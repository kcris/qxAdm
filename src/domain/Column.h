/*
 * Copyright (c) 2018, Kware, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from Kware,
 * or a written licence from an organisation licenced by Kware
 * to grant such a licence.
 */

#ifndef COLUMN_H
#define COLUMN_H

#include "commons.h"

struct ICell;
struct CellValueRetriever;
struct Sheet;
struct OutputColumn;

struct Column
{
  Column(const Sheet& sheet, const ColId & colId = ColId(), const QString & title = QString());
  virtual ~Column();

  const ColId & id() const {return m_colId;}
  const Sheet & sheet() const {return m_sheet;}
  const QString & getTitle() const {return m_title;}
  const QList<Column*> & components() const {return m_components;}

  int rowCount() const {return m_cells.size();}

  numeric_t getTotalData() const;
  numeric_t getTotalValue(const CellValueRetriever*) const;

  ICell* cellAt(int row) const;
  ICell* cellAt(const RowId & rowId) const;

  void insertRow(const RowId& newRowId, int index);
  void deleteRow(int index);

  void createCells();

  void addObserver(Column*);
  void removeObserver(Column*);
  void notify(const RowId & rowChanged) const;
  virtual void update(const RowId & rowChanged) const; //override this to react as observer

  virtual variant_t getSummary() const; //shown as last line in ui table
  virtual variant_t getDescription() const {return getSummary();} //tooltip for the last line in the ui table
protected:
  virtual ICell* createCell(const RowId& rowId, int index) const = 0;

protected:
  int findRow(const RowId& rowId) const;

  void addComponent(Column* pComponent) const; //allow 'composite' columns

public:
  numeric_t sumComponents(const RowId &rowId, const CellValueRetriever* pOutput) const;

protected:
  const Sheet& m_sheet;
  const ColId m_colId;
  QString m_title;
  QList<ICell*> m_cells;
  QList<Column*> m_observers;
  mutable QList<Column*> m_components;
};

#endif // COLUMN_H
