/*
 * Copyright (c) 2018, Kware, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from Kware,
 * or a written licence from an organisation licenced by Kware
 * to grant such a licence.
 */

#include "domain/OutputAutoSumColumn.h"

#include "domain/Cell.h"

struct ExplicitCell : public ICell
{
  ExplicitCell(const OutputAutoSumColumn& col, const RowId& rowId) : ICell(col, rowId), m_val(0) {}

  virtual bool isEditable() const override {return true;}
  virtual bool isNumeric() const override {return true;}
  virtual void setData(const variant_t & v) override {m_val = v.toDouble();m_column.notify(m_rowId);}
  virtual variant_t getData() const override {return m_val;}

  virtual bool isPartOfTotal() const override {return true;}
  virtual numeric_t getValue() const override {return m_val;}
  virtual QString getDescription() const override {return QString("%1").arg(m_val);}

private:
  numeric_t m_val;
};


OutputAutoSumColumn::OutputAutoSumColumn(const Sheet& sheet, const ColId & colId, const QString & title)
  : OutputColumn(sheet, colId, title)
{
}

ICell* OutputAutoSumColumn::createCell(const RowId& rowId, int /*index*/) const
{
  return new ExplicitCell(*this, rowId);
}
