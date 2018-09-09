/*
 * Copyright (c) 2018, Kware, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from Kware,
 * or a written licence from an organisation licenced by Kware
 * to grant such a licence.
 */

#ifndef ASOCDATA_H
#define ASOCDATA_H

#include "commons.h"

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QUuid>
#include <QtCore/QStringList>


//
// TODO: replace qtcore with std classes
//

struct AsocPersistence;

struct InvoiceData
{
  InvoiceData();

  QString issuer;
  numeric_t amount;
};

struct Person
{

};

struct Apartment
{
  //id
  //owner:person, mandatory
  //lodger:person, optional (if rent)

  //at a given time!? - timeline needed
};



struct LodgerData
{
  QUuid id;
  //QString name;
  QMap<QString, QString> inputText; //inputTitle->value
  QMap<QString, numeric_t> inputValues; //inputTitle->value
};

struct ColumnData
{
  ColumnData();

  QUuid id;
  QString name;
  QString type;
  QList<QString> invoices; //reference to sheet invoices

  numeric_t commonsPercent;
  QList<QString> commonsBy; //inputs titles

  numeric_t countedUnits;
  QList<QString> countedBy; //inputs titles

  QList<QString> dividedBy; //inputs titles
};

struct SheetData
{
  QString id;
  QMap<QString, numeric_t> invoices; //name -> value
  QList<ColumnData> columns;  //id -> ...
  QList<LodgerData> lodgers;  //id -> ...

  //TODO: add 'custom.inputs'
};

struct AsocData
{
  bool load(AsocPersistence& persist);
  bool save(AsocPersistence& persist) const;

  QString headerLeft;
  QString headerCenter;
  QString headerRight;

  QString footerLeft;
  QString footerCenter;
  QString footerRight;

  QMap<QString, SheetData> sheets;
};

#endif // ASOCDATA_H

