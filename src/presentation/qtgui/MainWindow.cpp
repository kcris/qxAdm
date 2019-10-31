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

  //load asoc data from file
  JsonPersistence persist("../../var/qa.json");
  persist.load(asoc);

  //copy asoc data into model/ui
  foreach(const SheetData & s, asoc.sheets)
    addSheetView(s.id);
}

MainWindow::~MainWindow()
{
  //copy asoc data from model/ui
  asoc.sheets.clear();
  for(int i = 0, n = ui->tabWidget->count(); i < n; ++i)
  {
    const QTableView* pTableView = static_cast<const QTableView*>(ui->tabWidget->widget(i));
    const SheetModel* pSheetModel = static_cast<const SheetModel*>(pTableView->model());

    const SheetData & sheetData = pSheetModel->sheet().save();
    asoc.sheets[sheetData.id] = sheetData;
  }

  //save asoc data to file
  JsonPersistence persist("../../var/qa.saved.json");
  persist.save(asoc);

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
  SheetData & sheetData = asoc.sheets.find(id).value();
  SheetModel* pModel = new SheetModel(this);

  pModel->sheet().load(sheetData);

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
