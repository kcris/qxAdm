/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Mon Jan 2 16:41:47 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_asoc;
    QAction *actionExit;
    QAction *actionEdit_Invoices;
    QAction *actionPrint;
    QAction *actionInput_Divider;
    QAction *actionInput_Counter;
    QAction *actionOutput_Explicit;
    QAction *actionOutput_Automatic;
    QAction *actionDelete_Column;
    QAction *actionAdd_Row;
    QAction *actionDelete_Row;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QTableView *tableView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuAsoc;
    QMenu *menuAdd_Column;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(852, 642);
        actionOpen_asoc = new QAction(MainWindow);
        actionOpen_asoc->setObjectName(QString::fromUtf8("actionOpen_asoc"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionEdit_Invoices = new QAction(MainWindow);
        actionEdit_Invoices->setObjectName(QString::fromUtf8("actionEdit_Invoices"));
        actionPrint = new QAction(MainWindow);
        actionPrint->setObjectName(QString::fromUtf8("actionPrint"));
        actionInput_Divider = new QAction(MainWindow);
        actionInput_Divider->setObjectName(QString::fromUtf8("actionInput_Divider"));
        actionInput_Counter = new QAction(MainWindow);
        actionInput_Counter->setObjectName(QString::fromUtf8("actionInput_Counter"));
        actionOutput_Explicit = new QAction(MainWindow);
        actionOutput_Explicit->setObjectName(QString::fromUtf8("actionOutput_Explicit"));
        actionOutput_Automatic = new QAction(MainWindow);
        actionOutput_Automatic->setObjectName(QString::fromUtf8("actionOutput_Automatic"));
        actionDelete_Column = new QAction(MainWindow);
        actionDelete_Column->setObjectName(QString::fromUtf8("actionDelete_Column"));
        actionAdd_Row = new QAction(MainWindow);
        actionAdd_Row->setObjectName(QString::fromUtf8("actionAdd_Row"));
        actionDelete_Row = new QAction(MainWindow);
        actionDelete_Row->setObjectName(QString::fromUtf8("actionDelete_Row"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tableView = new QTableView(tab);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout_2->addWidget(tableView);

        tabWidget->addTab(tab, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 852, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuAsoc = new QMenu(menuBar);
        menuAsoc->setObjectName(QString::fromUtf8("menuAsoc"));
        menuAdd_Column = new QMenu(menuAsoc);
        menuAdd_Column->setObjectName(QString::fromUtf8("menuAdd_Column"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuAsoc->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen_asoc);
        menuFile->addAction(actionExit);
        menuAsoc->addAction(actionEdit_Invoices);
        menuAsoc->addSeparator();
        menuAsoc->addAction(menuAdd_Column->menuAction());
        menuAsoc->addAction(actionDelete_Column);
        menuAsoc->addSeparator();
        menuAsoc->addAction(actionAdd_Row);
        menuAsoc->addAction(actionDelete_Row);
        menuAsoc->addSeparator();
        menuAsoc->addAction(actionPrint);
        menuAdd_Column->addAction(actionOutput_Automatic);
        menuAdd_Column->addAction(actionOutput_Explicit);
        menuAdd_Column->addAction(actionInput_Divider);
        menuAdd_Column->addAction(actionInput_Counter);
        mainToolBar->addSeparator();

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionOpen_asoc->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionEdit_Invoices->setText(QApplication::translate("MainWindow", "Edit Invoices", 0, QApplication::UnicodeUTF8));
        actionPrint->setText(QApplication::translate("MainWindow", "Print", 0, QApplication::UnicodeUTF8));
        actionInput_Divider->setText(QApplication::translate("MainWindow", "Input - Divider", 0, QApplication::UnicodeUTF8));
        actionInput_Counter->setText(QApplication::translate("MainWindow", "Input - Counter", 0, QApplication::UnicodeUTF8));
        actionOutput_Explicit->setText(QApplication::translate("MainWindow", "Output - Manual", 0, QApplication::UnicodeUTF8));
        actionOutput_Automatic->setText(QApplication::translate("MainWindow", "Output - Automatic", 0, QApplication::UnicodeUTF8));
        actionDelete_Column->setText(QApplication::translate("MainWindow", "Delete Column", 0, QApplication::UnicodeUTF8));
        actionAdd_Row->setText(QApplication::translate("MainWindow", "Add Row", 0, QApplication::UnicodeUTF8));
        actionDelete_Row->setText(QApplication::translate("MainWindow", "Delete Row", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Sheet", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuAsoc->setTitle(QApplication::translate("MainWindow", "Asoc", 0, QApplication::UnicodeUTF8));
        menuAdd_Column->setTitle(QApplication::translate("MainWindow", "Add Column", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
