/*
 * Copyright (c) 2018, Kware, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from Kware,
 * or a written licence from an organisation licenced by Kware
 * to grant such a licence.
 */

#ifndef SHEETMODEL_H
#define SHEETMODEL_H

#include <QtCore/QAbstractItemModel>

#include "domain/commons.h"
#include "domain/Column.h"
#include "domain/AsocData.h"
#include "domain/BasicColumns.h"
#include "domain/Sheet.h"

struct SheetModel : public QAbstractTableModel
                  , public ICellObserver
{
  SheetModel(SheetData& s, QObject* parent = nullptr);

  //implement ICellObserver
  virtual void update(int row, int col) override;

  //implement QAbstractTableModel
protected:
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  virtual QVariant data(const QModelIndex &index, int role) const override;
  virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
  //virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
  //virtual QModelIndex parent(const QModelIndex &index) const override;
private:
  Sheet m_sheet;
};

#endif // SHEETMODEL_H
