/*
 * Copyright (c) 2018, Kware, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from Kware,
 * or a written licence from an organisation licenced by Kware
 * to grant such a licence.
 */

#ifndef ASOCPERSISTENCE_H
#define ASOCPERSISTENCE_H

#include "domain/AsocData.h"

struct AsocPersistence
{
  virtual bool load(AsocData& asoc) const = 0;
  virtual bool save(const AsocData& asoc) const = 0;

  virtual ~AsocPersistence() = default;
};

#endif // ASOCPERSISTENCE_H
