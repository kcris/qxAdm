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

#include "EditInvoices.h"
#include "ui_EditInvoices.h"

EditInvoices::EditInvoices(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditInvoices)
{
    ui->setupUi(this);
}

EditInvoices::~EditInvoices()
{
    delete ui;
}
