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


#ifndef OUTPUTAUTOSPLITCOLUMN_H
#define OUTPUTAUTOSPLITCOLUMN_H

#include "BasicColumns.h"

class Invoice;
struct ICell;
struct OutputAutoSplitColumn;

//auto-split output component
struct SplitComponent : public OutputColumn
{
  SplitComponent(const Sheet& sheet, const QString & suffix, const OutputAutoSplitColumn & ownerCol);

  void addInputColumn(InputColumn*);

  numeric_t setAmount(const numeric_t & amount);
  numeric_t getAmount() const;

  virtual void update(const RowId & rowChanged) const; //override this to react as observer

  numeric_t getRowInputUnits(const RowId& rowId) const;
  numeric_t getUnitPrice() const;

protected:
  virtual void doSetAmount(const numeric_t & amount) = 0;
  numeric_t getInputsUnitsTotal() const;

//protected:
public:
  virtual ICell* createCell(const RowId& rowId, int index) const;

protected:
  numeric_t m_amount;
  mutable numeric_t m_pricePerUnit;
  QList<InputColumn*> m_inputs;
  const OutputAutoSplitColumn & m_ownerCol;
};

struct SplitCommonsComponent : public SplitComponent
{
  SplitCommonsComponent(const Sheet& sheet, const OutputAutoSplitColumn & ownerCol);

  void setPercent(double p) {m_percent = p;}

protected:
  virtual void doSetAmount(const numeric_t & amount);

private:
  double m_percent;
};


struct SplitCountedComponent : public SplitComponent
{
  SplitCountedComponent(const Sheet& sheet, const OutputAutoSplitColumn & ownerCol);

  void setCountedUnits(double u) {m_countedUnits = u;}

protected:
  virtual void doSetAmount(const numeric_t & amount);

private:
  double m_countedUnits;
};


struct SplitDividedComponent : public SplitComponent
{
  SplitDividedComponent(const Sheet& sheet, const OutputAutoSplitColumn & ownerCol);

protected:
  virtual void doSetAmount(const numeric_t & amount);
};


//
//auto-split output - composite of auto-split components
//
struct OutputAutoSplitColumn : public OutputColumn
{
  OutputAutoSplitColumn(const Sheet& sheet, const ColId & colId, const QString & title);
  virtual ~OutputAutoSplitColumn();

  //amount is the total of all invoices
  numeric_t getAmount() const;
  void splitAmount();

  void addInvoice(Invoice* pInvoice);
  void addSplitComponent(SplitComponent* pComponent) const;

protected:
  virtual ICell* createCell(const RowId& rowId, int index) const;

private:
  QList<Invoice*> m_invoices; //generates total amount to split
};

#endif // OUTPUTAUTOSPLITCOLUMN_H
