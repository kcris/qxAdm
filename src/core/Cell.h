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


#ifndef CELL_H
#define CELL_H

#include "commons.h"
#include "Column.h"


struct ICell
{
  ICell(const Column& col, const RowId& rowId) : m_column(col), m_rowId(rowId) {}
  virtual ~ICell() {}

  const RowId & rowId() const {return m_rowId;}
  //const ColId & colId() const {return m_column.id(); }

  void notify() const {m_column.notify(m_rowId);}

  virtual bool isEditable() const = 0;
  virtual bool isNumeric() const = 0;

  //user data
  virtual void setData(const variant_t & v) = 0;
  virtual variant_t getData() const = 0;

  //computed value
  virtual bool isPartOfTotal() const = 0;
  virtual numeric_t getValue(const OutputColumn*) const = 0;

protected:
  const Column& m_column;
  const RowId m_rowId;
};

#endif // CELL_H
