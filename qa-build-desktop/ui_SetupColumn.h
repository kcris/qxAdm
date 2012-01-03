/********************************************************************************
** Form generated from reading UI file 'SetupColumn.ui'
**
** Created: Mon Jan 2 23:01:39 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUPCOLUMN_H
#define UI_SETUPCOLUMN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SetupColumn
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_6;
    QLineEdit *lineEditOutputColumnName;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SetupColumn)
    {
        if (SetupColumn->objectName().isEmpty())
            SetupColumn->setObjectName(QString::fromUtf8("SetupColumn"));
        SetupColumn->resize(267, 69);
        verticalLayout = new QVBoxLayout(SetupColumn);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_6 = new QLabel(SetupColumn);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout->addWidget(label_6);

        lineEditOutputColumnName = new QLineEdit(SetupColumn);
        lineEditOutputColumnName->setObjectName(QString::fromUtf8("lineEditOutputColumnName"));

        horizontalLayout->addWidget(lineEditOutputColumnName);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(SetupColumn);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SetupColumn);
        QObject::connect(buttonBox, SIGNAL(accepted()), SetupColumn, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SetupColumn, SLOT(reject()));

        QMetaObject::connectSlotsByName(SetupColumn);
    } // setupUi

    void retranslateUi(QDialog *SetupColumn)
    {
        SetupColumn->setWindowTitle(QApplication::translate("SetupColumn", "Dialog", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("SetupColumn", "Column name:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SetupColumn: public Ui_SetupColumn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUPCOLUMN_H
