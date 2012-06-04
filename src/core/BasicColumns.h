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

#ifndef BASICCOLUMNS_H
#define BASICCOLUMNS_H

#include "Column.h"

//looks like a hack, but...original input values can be customized/overridden with other values
//
//If you don't want to create additional columns, our solution is to allow an input cell to return a value other
//than the 'real' one when a specific output cell (row, column) asks for the input
struct InputColumn : public Column
{
  InputColumn(const Sheet& sheet, const ColId & colId, const QString & title);

  //
  //NOTE: TODO move code below into SplitComponent::getCellValue
  //
//  //get our input value: real or overridden (if present)
//  numeric_t getInputValue(const numeric_t & referenceValue, const OutputColumn * pColumn, const RowId & forRow) const;

//  //store a custom/overridden value for my input (we'll return that later, when a specific output cell wants our value)
//  void setCustomInputValue(const OutputColumn * pColumn, const RowId & forRow);

private:
  //TODO: store array of custom values, for some outputcolumns
  //outputcolid,rowid -> numeric_t
};

struct OutputColumn : public Column
{
  OutputColumn(const Sheet& sheet, const ColId & colId, const QString & title);
};


struct StringColumn : public InputColumn
{
  StringColumn(const Sheet& sheet, const ColId & colId, const QString & title);
protected:
  virtual ICell* createCell(const RowId& rowId, int index) const;
  virtual variant_t getSummary() const;
};

struct TotalColumn : public OutputColumn
{
  TotalColumn(const Sheet& sheet, const ColId & colId, const QString & title);
protected:
  virtual ICell* createCell(const RowId& rowId, int index) const;
};

#endif // BASICCOLUMNS_H
