/*
 * Copyright (c) 2018, Kware, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from Kware,
 * or a written licence from an organisation licenced by Kware
 * to grant such a licence.
 */

#ifndef JSONPERSISTENCE_H
#define JSONPERSISTENCE_H

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QUuid>
#include <QtCore/QStringList>

#include "persistence/AsocPersistence.h"

struct JsonPersistence : public AsocPersistence
{
  JsonPersistence(const QString &jsonFilename);

  virtual bool load(AsocData& asoc) const override;
  virtual bool save(const AsocData& asoc) const override;

private:
  QString m_filename;
};


#endif // JSONPERSISTENCE_H

