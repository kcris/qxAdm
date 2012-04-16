#ifndef ASOCDATA_H
#define ASOCDATA_H

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QUuid>

struct InvoiceData
{
  InvoiceData();

  QString issuer;
  double amount;
};

struct LodgerData
{
  QUuid id;
  QString name;
  QMap<QString, double> inputValues; //inputTitle->value
};

struct ColumnData
{
  ColumnData();

  QUuid id;
  QString name;
  QString type;
  QList<QString> invoices; //reference to sheet invoices

  double commonsPercent;
  QList<QString> commonsBy; //inputs titles

  double countedUnits;
  QList<QString> countedBy; //inputs titles

  QList<QString> dividedBy; //inputs titles
};

struct SheetData
{
  QMap<QString, double> invoices; //name -> value
  QMap<QUuid, ColumnData> columns;  //id -> ...
  QList<LodgerData> lodgers;  //id -> ...

  //TODO: add 'custom.inputs'
};

struct AsocData
{
  bool load(const QString & jsonFilename);
  bool save(const QString & jsonFilename) const;

  QString headerLeft;
  QString headerCenter;
  QString headerRight;

  QString footerLeft;
  QString footerCenter;
  QString footerRight;

  QMap<QString, SheetData> sheets;
};

#endif // ASOCDATA_H
