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


#include "SetupAutoSplitColumn.h"
#include "ui_SetupAutoSplitColumn.h"

SetupAutoSplitColumn::SetupAutoSplitColumn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetupAutoSplitColumn)
{
    ui->setupUi(this);
}

SetupAutoSplitColumn::~SetupAutoSplitColumn()
{
    delete ui;
}
