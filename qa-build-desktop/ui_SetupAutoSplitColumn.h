/********************************************************************************
** Form generated from reading UI file 'SetupAutoSplitColumn.ui'
**
** Created: Mon Jan 2 23:01:39 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUPAUTOSPLITCOLUMN_H
#define UI_SETUPAUTOSPLITCOLUMN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SetupAutoSplitColumn
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_6;
    QLineEdit *lineEditOutputColumnName;
    QCheckBox *checkBoxShowOutputColumnAsComposite;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_4;
    QToolButton *toolButtonAddInvoice;
    QToolButton *toolButtonDelInvoice;
    QListView *listViewInvoices;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBoxEnableCommonsComponent;
    QDoubleSpinBox *doubleSpinBoxCommonsPercent;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *toolButtonAddCommonCoef;
    QToolButton *toolButtonDelCommonCoef;
    QListView *listViewCommonsCoefficients;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_9;
    QLineEdit *lineEditCommonsCoefficientsColumn;
    QFrame *line_3;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBoxEnableCountedComponent;
    QDoubleSpinBox *doubleSpinBoxCountedUnits;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *toolButtonAddCountedCoef;
    QToolButton *toolButtonDelCountedCoef;
    QListView *listViewCountedCoefficients;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_8;
    QLineEdit *lineEditCountedCoefficientsColumn;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBoxEnableDividedComponent;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButtonAddDividedCoef;
    QToolButton *toolButtonDelDividedCoef;
    QListView *listViewDividedCoefficients;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_7;
    QLineEdit *lineEditDividedCoefficientsColumn;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SetupAutoSplitColumn)
    {
        if (SetupAutoSplitColumn->objectName().isEmpty())
            SetupAutoSplitColumn->setObjectName(QString::fromUtf8("SetupAutoSplitColumn"));
        SetupAutoSplitColumn->resize(307, 665);
        verticalLayout_3 = new QVBoxLayout(SetupAutoSplitColumn);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_6 = new QLabel(SetupAutoSplitColumn);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_8->addWidget(label_6);

        lineEditOutputColumnName = new QLineEdit(SetupAutoSplitColumn);
        lineEditOutputColumnName->setObjectName(QString::fromUtf8("lineEditOutputColumnName"));

        horizontalLayout_8->addWidget(lineEditOutputColumnName);

        checkBoxShowOutputColumnAsComposite = new QCheckBox(SetupAutoSplitColumn);
        checkBoxShowOutputColumnAsComposite->setObjectName(QString::fromUtf8("checkBoxShowOutputColumnAsComposite"));
        checkBoxShowOutputColumnAsComposite->setChecked(true);

        horizontalLayout_8->addWidget(checkBoxShowOutputColumnAsComposite);


        verticalLayout_3->addLayout(horizontalLayout_8);

        groupBox = new QGroupBox(SetupAutoSplitColumn);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_7->addWidget(label_5);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_4);

        toolButtonAddInvoice = new QToolButton(groupBox);
        toolButtonAddInvoice->setObjectName(QString::fromUtf8("toolButtonAddInvoice"));

        horizontalLayout_7->addWidget(toolButtonAddInvoice);

        toolButtonDelInvoice = new QToolButton(groupBox);
        toolButtonDelInvoice->setObjectName(QString::fromUtf8("toolButtonDelInvoice"));

        horizontalLayout_7->addWidget(toolButtonDelInvoice);


        verticalLayout->addLayout(horizontalLayout_7);

        listViewInvoices = new QListView(groupBox);
        listViewInvoices->setObjectName(QString::fromUtf8("listViewInvoices"));

        verticalLayout->addWidget(listViewInvoices);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(SetupAutoSplitColumn);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        checkBoxEnableCommonsComponent = new QCheckBox(groupBox_2);
        checkBoxEnableCommonsComponent->setObjectName(QString::fromUtf8("checkBoxEnableCommonsComponent"));

        horizontalLayout_3->addWidget(checkBoxEnableCommonsComponent);

        doubleSpinBoxCommonsPercent = new QDoubleSpinBox(groupBox_2);
        doubleSpinBoxCommonsPercent->setObjectName(QString::fromUtf8("doubleSpinBoxCommonsPercent"));

        horizontalLayout_3->addWidget(doubleSpinBoxCommonsPercent);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        toolButtonAddCommonCoef = new QToolButton(groupBox_2);
        toolButtonAddCommonCoef->setObjectName(QString::fromUtf8("toolButtonAddCommonCoef"));

        horizontalLayout_3->addWidget(toolButtonAddCommonCoef);

        toolButtonDelCommonCoef = new QToolButton(groupBox_2);
        toolButtonDelCommonCoef->setObjectName(QString::fromUtf8("toolButtonDelCommonCoef"));

        horizontalLayout_3->addWidget(toolButtonDelCommonCoef);


        verticalLayout_2->addLayout(horizontalLayout_3);

        listViewCommonsCoefficients = new QListView(groupBox_2);
        listViewCommonsCoefficients->setObjectName(QString::fromUtf8("listViewCommonsCoefficients"));

        verticalLayout_2->addWidget(listViewCommonsCoefficients);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_11->addWidget(label_9);

        lineEditCommonsCoefficientsColumn = new QLineEdit(groupBox_2);
        lineEditCommonsCoefficientsColumn->setObjectName(QString::fromUtf8("lineEditCommonsCoefficientsColumn"));

        horizontalLayout_11->addWidget(lineEditCommonsCoefficientsColumn);


        verticalLayout_2->addLayout(horizontalLayout_11);

        line_3 = new QFrame(groupBox_2);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        checkBoxEnableCountedComponent = new QCheckBox(groupBox_2);
        checkBoxEnableCountedComponent->setObjectName(QString::fromUtf8("checkBoxEnableCountedComponent"));

        horizontalLayout_2->addWidget(checkBoxEnableCountedComponent);

        doubleSpinBoxCountedUnits = new QDoubleSpinBox(groupBox_2);
        doubleSpinBoxCountedUnits->setObjectName(QString::fromUtf8("doubleSpinBoxCountedUnits"));

        horizontalLayout_2->addWidget(doubleSpinBoxCountedUnits);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        toolButtonAddCountedCoef = new QToolButton(groupBox_2);
        toolButtonAddCountedCoef->setObjectName(QString::fromUtf8("toolButtonAddCountedCoef"));

        horizontalLayout_2->addWidget(toolButtonAddCountedCoef);

        toolButtonDelCountedCoef = new QToolButton(groupBox_2);
        toolButtonDelCountedCoef->setObjectName(QString::fromUtf8("toolButtonDelCountedCoef"));

        horizontalLayout_2->addWidget(toolButtonDelCountedCoef);


        verticalLayout_2->addLayout(horizontalLayout_2);

        listViewCountedCoefficients = new QListView(groupBox_2);
        listViewCountedCoefficients->setObjectName(QString::fromUtf8("listViewCountedCoefficients"));

        verticalLayout_2->addWidget(listViewCountedCoefficients);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_10->addWidget(label_8);

        lineEditCountedCoefficientsColumn = new QLineEdit(groupBox_2);
        lineEditCountedCoefficientsColumn->setObjectName(QString::fromUtf8("lineEditCountedCoefficientsColumn"));

        horizontalLayout_10->addWidget(lineEditCountedCoefficientsColumn);


        verticalLayout_2->addLayout(horizontalLayout_10);

        line = new QFrame(groupBox_2);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        checkBoxEnableDividedComponent = new QCheckBox(groupBox_2);
        checkBoxEnableDividedComponent->setObjectName(QString::fromUtf8("checkBoxEnableDividedComponent"));

        horizontalLayout->addWidget(checkBoxEnableDividedComponent);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        toolButtonAddDividedCoef = new QToolButton(groupBox_2);
        toolButtonAddDividedCoef->setObjectName(QString::fromUtf8("toolButtonAddDividedCoef"));

        horizontalLayout->addWidget(toolButtonAddDividedCoef);

        toolButtonDelDividedCoef = new QToolButton(groupBox_2);
        toolButtonDelDividedCoef->setObjectName(QString::fromUtf8("toolButtonDelDividedCoef"));

        horizontalLayout->addWidget(toolButtonDelDividedCoef);


        verticalLayout_2->addLayout(horizontalLayout);

        listViewDividedCoefficients = new QListView(groupBox_2);
        listViewDividedCoefficients->setObjectName(QString::fromUtf8("listViewDividedCoefficients"));

        verticalLayout_2->addWidget(listViewDividedCoefficients);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_9->addWidget(label_7);

        lineEditDividedCoefficientsColumn = new QLineEdit(groupBox_2);
        lineEditDividedCoefficientsColumn->setObjectName(QString::fromUtf8("lineEditDividedCoefficientsColumn"));

        horizontalLayout_9->addWidget(lineEditDividedCoefficientsColumn);


        verticalLayout_2->addLayout(horizontalLayout_9);


        verticalLayout_3->addWidget(groupBox_2);

        buttonBox = new QDialogButtonBox(SetupAutoSplitColumn);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_3->addWidget(buttonBox);


        retranslateUi(SetupAutoSplitColumn);
        QObject::connect(buttonBox, SIGNAL(accepted()), SetupAutoSplitColumn, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SetupAutoSplitColumn, SLOT(reject()));

        QMetaObject::connectSlotsByName(SetupAutoSplitColumn);
    } // setupUi

    void retranslateUi(QDialog *SetupAutoSplitColumn)
    {
        SetupAutoSplitColumn->setWindowTitle(QApplication::translate("SetupAutoSplitColumn", "Dialog", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("SetupAutoSplitColumn", "Column name:", 0, QApplication::UnicodeUTF8));
        checkBoxShowOutputColumnAsComposite->setText(QApplication::translate("SetupAutoSplitColumn", "Show as composite", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("SetupAutoSplitColumn", "Amount to split", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("SetupAutoSplitColumn", "Invoices", 0, QApplication::UnicodeUTF8));
        toolButtonAddInvoice->setText(QApplication::translate("SetupAutoSplitColumn", "+", 0, QApplication::UnicodeUTF8));
        toolButtonDelInvoice->setText(QApplication::translate("SetupAutoSplitColumn", "-", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("SetupAutoSplitColumn", "Split components", 0, QApplication::UnicodeUTF8));
        checkBoxEnableCommonsComponent->setText(QApplication::translate("SetupAutoSplitColumn", "Commons", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SetupAutoSplitColumn", "%", 0, QApplication::UnicodeUTF8));
        toolButtonAddCommonCoef->setText(QApplication::translate("SetupAutoSplitColumn", "+", 0, QApplication::UnicodeUTF8));
        toolButtonDelCommonCoef->setText(QApplication::translate("SetupAutoSplitColumn", "-", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("SetupAutoSplitColumn", "Show grouped inputs as column:", 0, QApplication::UnicodeUTF8));
        checkBoxEnableCountedComponent->setText(QApplication::translate("SetupAutoSplitColumn", "Counted", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SetupAutoSplitColumn", "total units", 0, QApplication::UnicodeUTF8));
        toolButtonAddCountedCoef->setText(QApplication::translate("SetupAutoSplitColumn", "+", 0, QApplication::UnicodeUTF8));
        toolButtonDelCountedCoef->setText(QApplication::translate("SetupAutoSplitColumn", "-", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("SetupAutoSplitColumn", "Show grouped inputs as column:", 0, QApplication::UnicodeUTF8));
        checkBoxEnableDividedComponent->setText(QApplication::translate("SetupAutoSplitColumn", "Divided", 0, QApplication::UnicodeUTF8));
        toolButtonAddDividedCoef->setText(QApplication::translate("SetupAutoSplitColumn", "+", 0, QApplication::UnicodeUTF8));
        toolButtonDelDividedCoef->setText(QApplication::translate("SetupAutoSplitColumn", "-", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("SetupAutoSplitColumn", "Show grouped inputs as column:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SetupAutoSplitColumn: public Ui_SetupAutoSplitColumn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUPAUTOSPLITCOLUMN_H
