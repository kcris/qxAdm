/*
 * Copyright (c) 2018, Kware, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from Kware,
 * or a written licence from an organisation licenced by Kware
 * to grant such a licence.
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
    explicit EditInvoices(QWidget *parent = nullptr);
    ~EditInvoices();

private:
    Ui::EditInvoices *ui;
};

#endif // EDITINVOICES_H
