/*
 * Copyright (c) 2018, Kware, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from Kware,
 * or a written licence from an organisation licenced by Kware
 * to grant such a licence.
 */

#include "domain/InputDivColumn.h"

#include "domain/Cell.h"

struct DivCell : public ICell
{
  DivCell(const InputDivColumn& col, const RowId& rowId) : ICell(col, rowId), m_div(0) {}

  virtual bool isEditable() const override {return true;}
  virtual bool isNumeric() const override {return true;}
  virtual void setData(const variant_t & v) override {m_div = v.toDouble(); m_column.notify(m_rowId);}
  virtual variant_t getData() const override {return m_div;}

  virtual bool isPartOfTotal() const override {return false;}
  virtual numeric_t getValue() const override {return m_div;}
  virtual QString getDescription() const override {return QString();}

private:
  numeric_t m_div;
};


InputDivColumn::InputDivColumn(const Sheet& sheet, const ColId & colId, const QString & title)
  : InputColumn(sheet, colId, title)
{
}

ICell* InputDivColumn::createCell(const RowId& rowId, int /*index*/) const
{
  return new DivCell(*this, rowId);
}
