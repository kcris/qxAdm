#ifndef ASOCDATA_H
#define ASOCDATA_H

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QUuid>

struct LodgerData
{
  QUuid id;
  QString name;
  QMap<QString, double> inputValues;
};

struct ColumnData
{
  QUuid id;
  QString name;
  QString type;
  QList<QString> invoices;

  double commonsPercent;
  QList<QUuid> commonsBy; //auto-split input columns

  double countedUnits;
  QList<QUuid> countedBy; //auto-split input columns

  QList<QUuid> dividedBy; //auto-split input columns
};

struct SheetData
{
  QMap<QString, double> invoices; //name -> value
  QMap<QUuid, ColumnData> columns;  //id -> ...
  QMap<QUuid, LodgerData> lodgers;  //id -> ...

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
