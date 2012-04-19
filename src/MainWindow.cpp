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


#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "core/Sheet.h"

AsocData asoc;

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    asoc.load("../var/qa.json");

    SheetData & sheet = asoc.sheets.find("2011.07").value();

    SheetModel* pModel = new SheetModel(sheet, this);
    ui->tableView->setModel(pModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//#include "TablePrintDialog.h"

void MainWindow::show()
{  
  QMainWindow::show();

  ui->tableView->resizeColumnsToContents();

  //QPrinter p;
  //TablePrintDialog dlg(ui->tableView, &p);
  //dlg.print();
}
