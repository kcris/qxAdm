/*
 * Copyright (c) 2018, Kware, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from Kware,
 * or a written licence from an organisation licenced by Kware
 * to grant such a licence.
 */

#include "presentation/qtgui/SetupAutoSplitColumn.h"
#include "ui_SetupAutoSplitColumn.h"

SetupAutoSplitColumn::SetupAutoSplitColumn(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SetupAutoSplitColumn)
{
    ui->setupUi(this);
}

SetupAutoSplitColumn::~SetupAutoSplitColumn()
{
    delete ui;
}
