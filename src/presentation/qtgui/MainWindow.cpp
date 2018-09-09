/*
 * Copyright (c) 2018, Kware, Timisoara
 * All rights reserved.
 *
 * Acquisition and use of this software and related materials for any
 * purpose requires a written licence agreement from Kware,
 * or a written licence from an organisation licenced by Kware
 * to grant such a licence.
 */

#include "presentation/qtgui/MainWindow.h"
#include "ui_MainWindow.h"

#include <QtWidgets/QTableView>
#include <QtWidgets/QHeaderView>

#include "persistence/json/JsonPersistence.h"
#include "presentation/qtgui/SheetModel.h"

static AsocData asoc;

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  JsonPersistence persist("../../var/qa.json");
  persist.load(asoc);

  foreach(const SheetData & s, asoc.sheets)
    addSheetView(s.id);
}

MainWindow::~MainWindow()
{
  JsonPersistence persist("../../var/qa.saved.json");
  persist.save(asoc);
  //asoc.save("../var/qa.test.json");

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
  pTableView->horizontalHeader()->setSectionsMovable(true);
  pTableView->horizontalHeader()->setDropIndicatorShown(true);

  QWidget* tab = new QWidget();
  QVBoxLayout* layout = new QVBoxLayout(tab);
  layout->addWidget(pTableView);

  ui->tabWidget->addTab(tab, id);
}


void MainWindow::on_actionOpen_asoc_triggered()
{

}
