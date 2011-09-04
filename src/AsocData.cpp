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

bool load(const QString & json, Asoc& asoc)
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

  Sheet sh;

  //sheet.invoices
  foreach (QVariant inv, sheet["invoices"].toList())
  {
    const QVariantMap invoices = inv.toMap();
    for (QVariantMap::const_iterator it = invoices.begin(), itEnd = invoices.end(); it != itEnd; ++it)
    {
      sh.invoices.insert(it.key(), it.value().toInt());
    }
  }

  //sheet.columns
  foreach (QVariant col, sheet["columns"].toList())
  {
    foreach (QVariant co, col.toMap())
    {
      QVariantMap column = co.toMap();

      const QString colId = column["id"].toString();

      Column c;
      c.name = column["name"].toString();
      c.type = column["type"].toString();
      //c.invoices = column["invoices"].toList();

      QVariantMap commons = column["commons"].toMap();
      c.commonsPercent = commons["percent"].toDouble();
      //c.commonsBy = commons["by"].toList();

      QVariantMap counted = column["counted"].toMap();
      c.countedUnits = counted["units"].toDouble();
      //c.countedBy = counted["by"].toList();

      QVariantMap divided = column["divided"].toMap();
      //c.dividedBy = divided["by"].toList();

      sh.columns.insert(colId, c);
    }
  }

  asoc.sheets.insert("2011.07", sh);

  return ok;
}

bool Asoc::load(const QString &jsonFilename)
{
  QFile file(jsonFilename);
  if (file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    const QString & json = file.readAll();
    return ::load(json, *this);
  }

  return false;
}

//bool Asoc::save(const QString &jsonFilename) const
//{
//  QFile file(jsonFilename);
//  if (file.open(QIODevice::WriteOnly | QIODevice::Text))
//  {
//    const QString & json = ::save(*this);
//    return 0 < file.write(json);
//  }

//  return false;
//}
