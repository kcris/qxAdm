/*
 * Copyright (c) 2018, Kware, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from Kware,
 * or a written licence from an organisation licenced by Kware
 * to grant such a licence.
 */

#ifndef SETUPCOLUMN_H
#define SETUPCOLUMN_H

#include <QDialog>

namespace Ui {
    class SetupColumn;
}

class SetupColumn : public QDialog
{
    Q_OBJECT

public:
    explicit SetupColumn(QWidget *parent = nullptr);
    ~SetupColumn();

private:
    Ui::SetupColumn *ui;
};

#endif // SETUPCOLUMN_H
