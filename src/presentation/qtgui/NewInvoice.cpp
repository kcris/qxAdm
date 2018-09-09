#include "NewInvoice.h"
#include "ui_NewInvoice.h"

NewInvoice::NewInvoice(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::NewInvoice)
{
  ui->setupUi(this);
}

NewInvoice::~NewInvoice()
{
  delete ui;
}
