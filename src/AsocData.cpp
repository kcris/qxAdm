#include "AsocData.h"

#include "qjson/src/parser.h"
#include "qjson/src/serializer.h"

#include <QtCore/QVariant>
#include <QtCore/QVariantMap>
#include <QtCore/QFile>

struct QVariantConvertException
{
  QVariantConvertException(const QString & err) : m_err(err) {}
private:
  QString m_err;
};

//throw exception if can't convert variant to desired type
QVariantMap toMap(QVariantMap & parent, const QString & name)
{
  QVariant v = parent[name];
  if (!v.isValid())
    throw QVariantConvertException(name + " field not found");

  if (!v.canConvert<QVariantMap>())
    throw QVariantConvertException("can't convert " + name + " to map");

  return v.toMap();
}

bool load(const QString & json, AsocData& asoc)
{
  QJson::Parser parser;
  bool ok = true;

  //root object
  QVariantMap root = parser.parse(json.toAscii(), &ok).toMap();
  if (!ok) {
    qFatal("An error occurred during parsing");
    return false;
  }

  QList<QString> inputColumns;

  //header
  QVariantMap asocHeader  = root["asoc.header"].toMap();
  asoc.headerLeft      = asocHeader["left"].toString();
  asoc.headerCenter    = asocHeader["center"].toString();
  asoc.headerRight     = asocHeader["right"].toString();

  //footer
  QVariantMap asocFooter  = root["asoc.footer"].toMap();
  asoc.footerLeft      = asocFooter["left"].toString();
  asoc.footerCenter    = asocFooter["center"].toString();
  asoc.footerRight     = asocFooter["right"].toString();

  QVariantList sheetsList = root["sheets"].toList();

  //sheet
  QVariantMap sheetItem = sheetsList.front().toMap(); //2011.07; TODO: read a specific sheet, by date
  QVariantMap sheet = sheetItem["2011.07"].toMap();

  SheetData sh;

  //sheet.invoices
  foreach (QVariant inv, sheet["invoices"].toList())
  {
    const QVariantMap invoices = inv.toMap();
    for (QVariantMap::const_iterator it = invoices.begin(), itEnd = invoices.end(); it != itEnd; ++it)
    {
      QString invName = it.key();
      double invValue = it.value().toDouble();

      sh.invoices.insert(invName, invValue);
    }
  }

  //sheet.columns
  foreach (QVariant col, sheet["columns"].toList())
  {
    QVariantMap column = col.toMap();

    if (column.isEmpty())
      continue;

    ColumnData c;
    c.id = column["id"].toString();
    c.name = column["name"].toString();
    c.type = column["type"].toString();
    foreach (QVariant inv, column["invoices"].toList())
    {
      c.invoices.append(inv.toString());
    }

    if (c.type.startsWith("input."))
    {
      inputColumns.append(c.name);
    }

    QVariantMap commons = column["commons"].toMap();
    if (!commons.isEmpty())
    {
      c.commonsPercent = commons["percent"].toDouble();
      foreach (QVariant byCom, commons["by"].toList())
        c.commonsBy.append(byCom.toString());
    }

    QVariantMap counted = column["counted"].toMap();
    if (!counted.isEmpty())
    {
      c.countedUnits = counted["units"].toDouble();
      foreach (QVariant byCnt, counted["by"].toList())
        c.countedBy.append(byCnt.toString());
    }

    QVariantMap divided = column["divided"].toMap();
    if (!divided.isEmpty())
    {
      foreach (QVariant byDiv, divided["by"].toList())
        c.countedBy.append(byDiv.toString());
    }

    sh.columns.insert(c.id, c);
  }

  //asoc.lodgers
  foreach (QVariant row, sheet["asoc.lodgers"].toList())
  {
    QVariantMap lodgerItem = row.toMap();

    if (lodgerItem.isEmpty())
      continue;

    LodgerData lodger;
    lodger.id = lodgerItem["id"].toString();
    lodger.name = lodgerItem["name"].toString();

    foreach(QString inp, inputColumns)
    {
      QVariant val = lodgerItem[inp];
      if (!val.isNull())
        lodger.inputValues.insert(inp, val.toDouble());
    }

    sh.lodgers.append(lodger);
  }

  //TODO: all sheets + with right id
  asoc.sheets.insert("2011.07", sh);

  return ok;
}

bool AsocData::load(const QString &jsonFilename)
{
  QFile file(jsonFilename);
  if (file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    const QString & json = file.readAll();
    return ::load(json, *this);
  }

  return false;
}

//bool AsocData::save(const QString &jsonFilename) const
//{
//  QFile file(jsonFilename);
//  if (file.open(QIODevice::WriteOnly | QIODevice::Text))
//  {
//    const QString & json = ::save(*this);
//    return 0 < file.write(json);
//  }

//  return false;
//}
