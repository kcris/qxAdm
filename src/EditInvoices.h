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

#ifndef EDITINVOICES_H
#define EDITINVOICES_H

#include <QDialog>

namespace Ui {
    class EditInvoices;
}

class EditInvoices : public QDialog
{
    Q_OBJECT

public:
    explicit EditInvoices(QWidget *parent = 0);
    ~EditInvoices();

private:
    Ui::EditInvoices *ui;
};

#endif // EDITINVOICES_H
