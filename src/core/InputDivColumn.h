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


#ifndef INPUTDIVCOLUMN_H
#define INPUTDIVCOLUMN_H

#include "BasicColumns.h"

struct ICell;

struct InputDivColumn : public InputColumn
{
  InputDivColumn(const Sheet& sheet, const ColId & colId, const QString & title);
protected:
  virtual ICell* createCell(const RowId& rowId, int index) const;
};

#endif // INPUTDIVCOLUMN_H
