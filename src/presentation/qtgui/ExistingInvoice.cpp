#include "ExistingInvoice.h"
#include "ui_ExistingInvoice.h"

ExistingInvoice::ExistingInvoice(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ExistingInvoice)
{
  ui->setupUi(this);
}

ExistingInvoice::~ExistingInvoice()
{
  delete ui;
}
