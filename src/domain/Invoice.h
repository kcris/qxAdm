/*
 * Copyright (c) 2018, Kware, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from Kware,
 * or a written licence from an organisation licenced by Kware
 * to grant such a licence.
 */

#ifndef INVOICE_H
#define INVOICE_H

#include "commons.h"

struct Invoice
{
  Invoice(const numeric_t & a, const QString & d) : m_amount(a), m_description(d) {}

  numeric_t m_amount;
  QString m_description;
};

#endif // INVOICE_H
