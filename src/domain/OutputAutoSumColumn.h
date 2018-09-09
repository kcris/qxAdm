/*
 * Copyright (c) 2018, Kware, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from Kware,
 * or a written licence from an organisation licenced by Kware
 * to grant such a licence.
 */

#ifndef OUTPUTAUTOSUMCOLUMN_H
#define OUTPUTAUTOSUMCOLUMN_H

#include "BasicColumns.h"

struct ICell;

//explicit output
struct OutputAutoSumColumn : public OutputColumn
{
  OutputAutoSumColumn(const Sheet& sheet, const ColId & colId, const QString & title);
protected:
  virtual ICell* createCell(const RowId& rowId, int index) const override;
};

#endif // OUTPUTAUTOSUMCOLUMN_H
