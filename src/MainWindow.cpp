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

#include <QtGui/QTableView>

#include "core/Sheet.h"

AsocData asoc;

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    asoc.load("../var/qa.json");

    foreach(const SheetData & s, asoc.sheets)
      addSheetView(s.id);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//#include "TablePrintDialog.h"

void MainWindow::show()
{  
  QMainWindow::show();


  //QPrinter p;
  //TablePrintDialog dlg(ui->tableView, &p);
  //dlg.print();
}

void MainWindow::addSheetView(const QString & id)
{
  SheetData & sheet = asoc.sheets.find(id).value();
  SheetModel* pModel = new SheetModel(sheet, this);

  QTableView* pTableView = new QTableView(this);
  pTableView->setModel(pModel);

  pTableView->resizeColumnsToContents();
  pTableView->horizontalHeader()->setMovable(true);
  pTableView->horizontalHeader()->setDropIndicatorShown(true);

  QWidget* tab = new QWidget();
  QVBoxLayout* layout = new QVBoxLayout(tab);
  layout->addWidget(pTableView);

  ui->tabWidget->addTab(tab, id);
}

