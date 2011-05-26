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



#include "InputDivColumn.h"

#include "Cell.h"

struct DivCell : public ICell
{
  DivCell(const InputDivColumn& col, const RowId& rowId) : ICell(col, rowId), m_div(1) {}

  virtual bool isEditable() const {return true;}
  virtual bool isNumeric() const {return true;}
  virtual void setData(const variant_t & v) {m_div = v.toDouble(); m_column.notify(m_rowId);}
  virtual variant_t getData() const {return m_div;}

  virtual bool isPartOfTotal() const {return false;}
  virtual numeric_t getValue(const OutputColumn* pColumn) const {return static_cast<const InputDivColumn &>(m_column).getInputValue(m_div, pColumn, m_rowId);}

private:
  numeric_t m_div;
};


InputDivColumn::InputDivColumn(const Sheet& sheet, const ColId & colId, const QString & title)
  : InputColumn(sheet, colId, title)
{
}

ICell* InputDivColumn::createCell(const RowId& rowId, int index) const
{
  return new DivCell(*this, rowId);
}
