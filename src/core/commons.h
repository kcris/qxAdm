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
