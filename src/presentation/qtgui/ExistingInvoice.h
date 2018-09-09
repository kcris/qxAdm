#ifndef EXISTINGINVOICE_H
#define EXISTINGINVOICE_H

#include <QDialog>

namespace Ui {
class ExistingInvoice;
}

class ExistingInvoice : public QDialog
{
  Q_OBJECT

public:
  explicit ExistingInvoice(QWidget *parent = nullptr);
  ~ExistingInvoice();

private:
  Ui::ExistingInvoice *ui;
};

#endif // EXISTINGINVOICE_H
