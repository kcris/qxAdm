/*
 * Copyright (c) 2018, Kware, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from Kware,
 * or a written licence from an organisation licenced by Kware
 * to grant such a licence.
 */

#include "domain/AsocData.h"

#include "persistence/AsocPersistence.h"

InvoiceData::InvoiceData()
  : amount(0)
{
}

ColumnData::ColumnData()
  : commonsPercent(0)
  , countedUnits(0)
{
}


bool AsocData::load(AsocPersistence& persist)
{
  return persist.load(*this);
}

bool AsocData::save(AsocPersistence& persist) const
{
  return persist.save(*this);
}
