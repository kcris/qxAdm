#ifndef ASOCDATA_H
#define ASOCDATA_H

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QUuid>

struct Column
{
  QString name;
  QString type;
  QList<QString> invoices;

  double commonsPercent;
  QList<QUuid> commonsBy; //auto-split input columns

  double countedUnits;
  QList<QUuid> countedBy; //auto-split input columns

  QList<QUuid> dividedBy; //auto-split input columns
};

struct Sheet
{
  QMap<QString, double> invoices; //name -> value
  QMap<QUuid, Column> columns;  //id -> ...
};

struct Asoc
{
  QString headerLeft;
  QString headerCenter;
  QString headerRight;

  QString footerLeft;
  QString footerCenter;
  QString footerRight;

  QMap<QString, Sheet> sheets;
};

#endif // ASOCDATA_H
