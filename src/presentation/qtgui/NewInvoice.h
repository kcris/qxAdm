#ifndef NEWINVOICE_H
#define NEWINVOICE_H

#include <QDialog>

namespace Ui {
class NewInvoice;
}

class NewInvoice : public QDialog
{
  Q_OBJECT

public:
  explicit NewInvoice(QWidget *parent = nullptr);
  ~NewInvoice();

private:
  Ui::NewInvoice *ui;
};

#endif // NEWINVOICE_H
