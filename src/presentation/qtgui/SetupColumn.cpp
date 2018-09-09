/*
 * Copyright (c) 2018, Kware, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from Kware,
 * or a written licence from an organisation licenced by Kware
 * to grant such a licence.
 */

#include "presentation/qtgui/SetupColumn.h"
#include "ui_SetupColumn.h"

SetupColumn::SetupColumn(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SetupColumn)
{
    ui->setupUi(this);
}

SetupColumn::~SetupColumn()
{
    delete ui;
}
