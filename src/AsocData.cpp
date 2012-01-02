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
  QVariantMap sheetData = sheetsList.front().toMap(); //TODO: read a specific sheet, by date
  QVariantMap sheet = sheetData["2011.07"].toMap();

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

//  {
//    ColumnData* ccc = new ColumnData();
//    delete ccc; // no crash here

//    ColumnData cc;
//    cc.name = "";
//    //but dtor CRASHes here!?!?!
//  }

  //sheet.columns
  foreach (QVariant col, sheet["columns"].toList())
  {
    QVariantMap column = col.toMap();

    if (column.isEmpty())
      continue;

    const QString colId = column["id"].toString();

    ColumnData c;
    c.name = column["name"].toString();
    c.type = column["type"].toString();
    foreach (QVariant inv, column["invoices"].toList())
    {
      c.invoices.append(inv.toString());
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

    sh.columns.insert(colId, c);
  }

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
