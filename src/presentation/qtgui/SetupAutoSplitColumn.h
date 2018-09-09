/*
 * Copyright (c) 2018, Kware, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from Kware,
 * or a written licence from an organisation licenced by Kware
 * to grant such a licence.
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
    explicit SetupAutoSplitColumn(QWidget *parent = nullptr);
    ~SetupAutoSplitColumn();

private:
    Ui::SetupAutoSplitColumn *ui;
};

#endif // SETUPAUTOSPLITCOLUMN_H
