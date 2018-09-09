/*
 * Copyright (c) 2018, Kware, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from Kware,
 * or a written licence from an organisation licenced by Kware
 * to grant such a licence.
 */

#ifndef OUTPUTAUTOSPLITCOLUMN_H
#define OUTPUTAUTOSPLITCOLUMN_H

#include "BasicColumns.h"

#include "Cell.h"

struct Invoice;
//struct ICell;
struct OutputAutoSplitColumn;

//auto-split output component
struct SplitComponent : public OutputColumn
                      , public CellValueRetriever
{
  SplitComponent(const Sheet& sheet, const QString & title, const OutputAutoSplitColumn & ownerCol);

  virtual variant_t getDescription() const override;

  //implement CellValueRetriever (to customize inputs handling)
  virtual numeric_t getCellValue(const ICell & cell, const numeric_t & value) const override;
  virtual QString getCellDescription(const ICell & cell, const QString & description) const override;

  void addInputColumn(const InputColumn*);

  numeric_t setAmount(const numeric_t & amount);
  numeric_t getAmount() const;

  virtual void update(const RowId & rowChanged) const override; //override this to react as observer

  numeric_t getRowInputUnits(const RowId& rowId) const;
  numeric_t getUnitPrice() const;

protected:
  virtual void doSetAmount(const numeric_t & amount) = 0;
  numeric_t getInputsUnitsTotal() const;

//protected:
public:
  virtual ICell* createCell(const RowId& rowId, int index) const override;

protected:
  numeric_t m_amount;
  mutable numeric_t m_pricePerUnit;
  QList<const InputColumn*> m_inputs;
  const OutputAutoSplitColumn & m_ownerCol;
};

struct SplitCommonsComponent : public SplitComponent
{
  SplitCommonsComponent(const Sheet& sheet, const OutputAutoSplitColumn & ownerCol);

  void setPercent(numeric_t p) {m_percent = p;}

protected:
  virtual void doSetAmount(const numeric_t & amount) override;

private:
  numeric_t m_percent;
};


struct SplitCountedComponent : public SplitComponent
{
  SplitCountedComponent(const Sheet& sheet, const OutputAutoSplitColumn & ownerCol);

  void setCountedUnits(numeric_t u) {m_countedUnits = u;}

protected:
  virtual void doSetAmount(const numeric_t & amount) override;

private:
  numeric_t m_countedUnits;
};


struct SplitDividedComponent : public SplitComponent
{
  SplitDividedComponent(const Sheet& sheet, const OutputAutoSplitColumn & ownerCol);

protected:
  virtual void doSetAmount(const numeric_t & amount) override;
};


//
//auto-split output - composite of auto-split components
//
struct OutputAutoSplitColumn : public OutputColumn
{
  OutputAutoSplitColumn(const Sheet& sheet, const ColId & colId, const QString & title);
  virtual ~OutputAutoSplitColumn();

  virtual variant_t getDescription() const override;

  //amount is the total of all invoices
  numeric_t getAmount() const;
  void splitAmount();

  void addInvoice(Invoice* pInvoice);
  void addSplitComponent(SplitComponent* pComponent) const;

  SplitComponent* getSplitComponent(const QString & title) const;
protected:
  virtual ICell* createCell(const RowId& rowId, int index) const override;

private:
  QList<Invoice*> m_invoices; //generates total amount to split
};

#endif // OUTPUTAUTOSPLITCOLUMN_H
