/*
 * Copyright (c) 2018, Kware, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from Kware,
 * or a written licence from an organisation licenced by Kware
 * to grant such a licence.
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
  virtual QString getCellDescription(const ICell & cell, const QString & description) const = 0;
};


struct ICell
{
  ICell(const Column& col, const RowId& rowId) : m_column(col), m_rowId(rowId) {}
  virtual ~ICell() = default;

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
  virtual QString getDescription() const = 0;

public:
  numeric_t getValue(const CellValueRetriever * pRetr) const
  {
    const numeric_t val = getValue();

    return pRetr ? pRetr->getCellValue(*this, val) : val;
  }

  QString getDescription(const CellValueRetriever * pRetr) const
  {
    const QString desc = getDescription();

    return pRetr ? pRetr->getCellDescription(*this, desc) : desc;
  }

protected:
  const Column& m_column;
  const RowId m_rowId;
};

#endif // CELL_H
