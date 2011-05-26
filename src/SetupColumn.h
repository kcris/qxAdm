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
    explicit SetupColumn(QWidget *parent = 0);
    ~SetupColumn();

private:
    Ui::SetupColumn *ui;
};

#endif // SETUPCOLUMN_H
