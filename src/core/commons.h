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


#ifndef COMMONS_H
#define COMMONS_H

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QUuid>
#include <QtCore/QVariant>

/*custom data types*/

//typedef QUuid       uuid_t;
//typedef QString     string_t;
typedef double      numeric_t;
typedef QVariant    variant_t;

/* compare floating numbers using finite precision */
inline bool compareNumeric(const numeric_t & n1, const numeric_t & n2)
{
  static const int f = 10; //precision factor - not all decimals are interesting

  const int x1 = n1 * f;
  const int x2 = n2 * f;

  return x1 == x2;
}
//TODO: consider creating a class for numeric_t to avoid FP rounding issues?

/**
 * using UUIDs as row/column ids
 *
 * note: this is required since rows/columns have to be identified across sheets
 *
 * a simple row/column index is not usable for cross-sheet identification (however, a local index *is* usable inside one sheet)
 */
struct RowId : public QUuid
{
  RowId() : QUuid() {}
  RowId(const QUuid & uuid) : QUuid(uuid) {}
  bool operator==(const RowId & other) const {return QUuid::operator ==(other);}
};

struct ColId : public QUuid
{
  ColId() : QUuid() {}
  ColId(const QUuid & uuid) : QUuid(uuid) {}
};

//TODO: timeline sequencer (generates timeline; default=monthly)

#endif // COMMONS_H
