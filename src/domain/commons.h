/*
 * Copyright (c) 2018, Kware, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from Kware,
 * or a written licence from an organisation licenced by Kware
 * to grant such a licence.
 */

#ifndef COMMONS_H
#define COMMONS_H

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QUuid>
#include <QtCore/QVariant>

//external libs
#include "external/gtest/FloatingPoint.h" //floating point support, taken from googletest
//#include "external/uuid/uuid.h"  //uuid, taken from std proposal
#include "external/self/uuid.hpp"  //experimental, self test

/*custom data types*/

//typedef QUuid       uuid_t;
//typedef QString     string_t;
typedef double      numeric_t;
typedef QVariant    variant_t;

/* compare floating numbers using finite precision */
inline bool compareNumeric(const numeric_t & left, const numeric_t & right)
{
  //https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
  static_assert(std::is_same<numeric_t, double>::value || std::is_same<numeric_t, float>::value, "FloatingPoint works for double or float");

  const FloatingPoint<numeric_t> lhs(left), rhs(right);

  return lhs.AlmostEquals(rhs);
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
