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

struct ICell;

//
// reader of a cell's value may 'visit' (intercept) the cell to customize the resulting value
//
struct CellValueRetriever
{
  virtual ~CellValueRetriever() {}

  virtual numeric_t getCellValue(const ICell & cell, const numeric_t & value) const = 0;
};


struct ICell
{
  ICell(const Column& col, const RowId& rowId) : m_column(col), m_rowId(rowId) {}
  virtual ~ICell() {}

  //const Column & column() const {return m_column; }
  const RowId & rowId() const {return m_rowId;}

  void notify() const {m_column.notify(m_rowId);}

  virtual bool isEditable() const = 0;
  virtual bool isNumeric() const = 0;

  //user data
  virtual void setData(const variant_t & v) = 0;
  virtual variant_t getData() const = 0;

  //computed value
  virtual bool isPartOfTotal() const = 0;
private:
  virtual numeric_t getValue() const = 0;

public:
  numeric_t getValue(const CellValueRetriever * pRetr) const
  {
    const numeric_t val = getValue();

    return pRetr ? pRetr->getCellValue(*this, val) : val;
  }

protected:
  const Column& m_column;
  const RowId m_rowId;
};

#endif // CELL_H
