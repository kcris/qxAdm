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


#include "Cell.h"
#include "BasicColumns.h"
#include "Sheet.h"

struct StringCell : public ICell
{
  StringCell(const Column& col, const RowId& rowId) : ICell(col, rowId) {}

  virtual bool isEditable() const {return true;}
  virtual bool isNumeric() const {return false;}
  virtual void setData(const variant_t & v) {m_string = v.toString();}
  virtual variant_t getData() const {return m_string;}

  virtual bool isPartOfTotal() const {return false;}
  virtual numeric_t getValue(const OutputColumn*) const {return 0;}

private:
  QString m_string;
};


StringColumn::StringColumn(const Sheet& sheet, const ColId & colId, const QString & title)
  : InputColumn(sheet, colId, title)
{
}

ICell* StringColumn::createCell(const RowId& rowId, int index) const
{
  return new StringCell(*this, rowId);
}



struct TotalCell : public ICell
{
  TotalCell(const Column& col, const RowId& rowId) : ICell(col, rowId) {}

  virtual bool isEditable() const {return false;}
  virtual bool isNumeric() const {return true;}
  virtual void setData(const variant_t & /*v*/) {Q_ASSERT(false);}
  virtual variant_t getData() const {Q_ASSERT(false);return getValue(NULL);}

  virtual bool isPartOfTotal() const {return false;}
  virtual numeric_t getValue(const OutputColumn*) const { return m_column.sheet().totalRowValue(m_rowId); } //auto calculate row total
};


TotalColumn::TotalColumn(const Sheet& sheet, const ColId & colId, const QString & title)
  : OutputColumn(sheet, colId, title)
{
}

ICell* TotalColumn::createCell(const RowId& rowId, int index) const
{
  return new TotalCell(*this, rowId);
}
