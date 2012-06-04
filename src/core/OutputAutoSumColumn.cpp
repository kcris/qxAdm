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



#include "OutputAutoSumColumn.h"

#include "Cell.h"

struct ExplicitCell : public ICell
{
  ExplicitCell(const OutputAutoSumColumn& col, const RowId& rowId) : ICell(col, rowId), m_val(0) {}

  virtual bool isEditable() const {return true;}
  virtual bool isNumeric() const {return true;}
  virtual void setData(const variant_t & v) {m_val = v.toDouble();m_column.notify(m_rowId);}
  virtual variant_t getData() const {return m_val;}

  virtual bool isPartOfTotal() const {return true;}
  virtual numeric_t getValue() const {return m_val;}

private:
  numeric_t m_val;
};


OutputAutoSumColumn::OutputAutoSumColumn(const Sheet& sheet, const ColId & colId, const QString & title)
  : OutputColumn(sheet, colId, title)
{
}

ICell* OutputAutoSumColumn::createCell(const RowId& rowId, int index) const
{
  return new ExplicitCell(*this, rowId);
}
