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


/**
 * base class for all inputs/coefficients columns
 */
InputColumn::InputColumn(const Sheet& sheet, const ColId & colId, const QString & title)
  : Column(sheet, colId, title)
{
}

//numeric_t InputColumn::getInputValue(const numeric_t & referenceValue, const OutputColumn * pColumn, const RowId & forRow) const
//{
//  numeric_t value = referenceValue;

//  if (pColumn)
//  {
//    //TODO: search in custom values
//  }

//  return value;
//}

//void InputColumn::setCustomInputValue(const OutputColumn * pColumn, const RowId & forRow)
//{
//  //store a map of custom values (per row, per output column)
//}




/**
 * base class for all outputs/amounts columns
 */
OutputColumn::OutputColumn(const Sheet& sheet, const ColId & colId, const QString & title)
  : Column(sheet, colId, title)
{
}



struct StringCell : public ICell
{
  StringCell(const Column& col, const RowId& rowId) : ICell(col, rowId) {}

  virtual bool isEditable() const {return true;}
  virtual bool isNumeric() const {return false;}
  virtual void setData(const variant_t & v) {m_string = v.toString();}
  virtual variant_t getData() const {return m_string;}

  virtual bool isPartOfTotal() const {return false;}
  virtual numeric_t getValue() const {return 1.0;}

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

variant_t StringColumn::getSummary() const
{
  return "TOTAL";
}



struct TotalCell : public ICell
{
  TotalCell(const Column& col, const RowId& rowId) : ICell(col, rowId) {}

  virtual bool isEditable() const {return false;}
  virtual bool isNumeric() const {return true;}
  virtual void setData(const variant_t & /*v*/) { Q_ASSERT(false); }
  virtual variant_t getData() const { Q_ASSERT(false);return getValue(); }

  virtual bool isPartOfTotal() const {return false;}
  virtual numeric_t getValue() const { return m_column.sheet().totalRowValue(m_rowId); } //auto calculate row total
};


TotalColumn::TotalColumn(const Sheet& sheet, const ColId & colId, const QString & title)
  : OutputColumn(sheet, colId, title)
{
}

ICell* TotalColumn::createCell(const RowId& rowId, int index) const
{
  return new TotalCell(*this, rowId);
}


