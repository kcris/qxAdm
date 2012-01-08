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

#include "Column.h"

class Invoice;
struct ICell;
struct OutputAutoSplitColumn;

//auto-split output component
struct SplitComponent : public OutputColumn
{
  SplitComponent(const Sheet& sheet, const QString & suffix, const OutputAutoSplitColumn & ownerCol);

  void addInputColumn(InputColumn*);

  numeric_t setAmount(double amount);
  numeric_t getAmount() const;

  numeric_t computeCellValue(const RowId& rowId) const;

  virtual void update(const RowId & rowChanged) const; //override this to react as observer

private:
  numeric_t getRowInputUnits(const RowId& rowId) const;
  numeric_t getUnitPrice() const;

protected:
  virtual void doSetAmount(numeric_t amount) = 0;
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
  virtual void doSetAmount(numeric_t amount);

private:
  int m_percent;
};


struct SplitCountedComponent : public SplitComponent
{
  SplitCountedComponent(const Sheet& sheet, const OutputAutoSplitColumn & ownerCol);

  void setCountedUnits(double u) {m_countedUnits = u;}

protected:
  virtual void doSetAmount(numeric_t amount);

private:
  double m_countedUnits;
};


struct SplitDividedComponent : public SplitComponent
{
  SplitDividedComponent(const Sheet& sheet, const OutputAutoSplitColumn & ownerCol);

protected:
  virtual void doSetAmount(numeric_t amount);
};


//
//composite output - a generic container of auto-split components
//
//see also: CompositeColumn - cleanup??? remove CompositeAutoSplitOutputColumn?
//
struct CompositeAutoSplitOutputColumn : public OutputColumn
{
  CompositeAutoSplitOutputColumn(const Sheet& sheet, const ColId & colId, const QString & title);
  virtual ~CompositeAutoSplitOutputColumn();

  numeric_t getAmount() const;
  void splitAmount();

  numeric_t computeCellValue(const RowId& rowId) const;

  void addInvoice(Invoice* pInvoice);
protected:
  void addComponent(SplitComponent* pComponent);

protected:
  QList<Invoice*> m_invoices; //generates total amount to split
  QList<SplitComponent*> m_components;
};


//typical automatic output
struct OutputAutoSplitColumn : public CompositeAutoSplitOutputColumn
{
  OutputAutoSplitColumn(const Sheet& sheet, const ColId & colId, const QString & title);

  void setCommonsPercent(double p) {m_commons->setPercent(p);}
  void setCountedUnits(double u) {m_counted->setCountedUnits(u);}

  void addCommonsInput(InputColumn* pInputCol) {m_commons->addInputColumn(pInputCol);}
  void addCountedInput(InputColumn* pInputCol) {m_counted->addInputColumn(pInputCol);}
  void addDividedInput(InputColumn* pInputCol) {m_divided->addInputColumn(pInputCol);}
protected:
  virtual ICell* createCell(const RowId& rowId, int index) const;
private:
  SplitCommonsComponent* m_commons;
  SplitCountedComponent* m_counted;
  SplitDividedComponent* m_divided;
};

#endif // OUTPUTAUTOSPLITCOLUMN_H
