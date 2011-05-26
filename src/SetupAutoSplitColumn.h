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


#ifndef SETUPAUTOSPLITCOLUMN_H
#define SETUPAUTOSPLITCOLUMN_H

#include <QDialog>

namespace Ui {
    class SetupAutoSplitColumn;
}

class SetupAutoSplitColumn : public QDialog
{
    Q_OBJECT

public:
    explicit SetupAutoSplitColumn(QWidget *parent = 0);
    ~SetupAutoSplitColumn();

private:
    Ui::SetupAutoSplitColumn *ui;
};

#endif // SETUPAUTOSPLITCOLUMN_H
