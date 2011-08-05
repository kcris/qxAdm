/********************************************************************************
** Form generated from reading UI file 'EditInvoices.ui'
**
** Created: Fri May 27 15:09:12 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITINVOICES_H
#define UI_EDITINVOICES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableView>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_EditInvoices
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButtonAddInvoice;
    QToolButton *toolButtonDelInvoice;
    QTableView *tableViewInvoices;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *EditInvoices)
    {
        if (EditInvoices->objectName().isEmpty())
            EditInvoices->setObjectName(QString::fromUtf8("EditInvoices"));
        EditInvoices->resize(400, 484);
        verticalLayout = new QVBoxLayout(EditInvoices);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(EditInvoices);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        toolButtonAddInvoice = new QToolButton(EditInvoices);
        toolButtonAddInvoice->setObjectName(QString::fromUtf8("toolButtonAddInvoice"));

        horizontalLayout->addWidget(toolButtonAddInvoice);

        toolButtonDelInvoice = new QToolButton(EditInvoices);
        toolButtonDelInvoice->setObjectName(QString::fromUtf8("toolButtonDelInvoice"));

        horizontalLayout->addWidget(toolButtonDelInvoice);


        verticalLayout->addLayout(horizontalLayout);

        tableViewInvoices = new QTableView(EditInvoices);
        tableViewInvoices->setObjectName(QString::fromUtf8("tableViewInvoices"));

        verticalLayout->addWidget(tableViewInvoices);

        buttonBox = new QDialogButtonBox(EditInvoices);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(EditInvoices);
        QObject::connect(buttonBox, SIGNAL(accepted()), EditInvoices, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), EditInvoices, SLOT(reject()));

        QMetaObject::connectSlotsByName(EditInvoices);
    } // setupUi

    void retranslateUi(QDialog *EditInvoices)
    {
        EditInvoices->setWindowTitle(QApplication::translate("EditInvoices", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("EditInvoices", "Invoices of the current sheet:", 0, QApplication::UnicodeUTF8));
        toolButtonAddInvoice->setText(QApplication::translate("EditInvoices", "+", 0, QApplication::UnicodeUTF8));
        toolButtonDelInvoice->setText(QApplication::translate("EditInvoices", "-", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EditInvoices: public Ui_EditInvoices {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITINVOICES_H
