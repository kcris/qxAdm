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
