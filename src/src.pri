SOURCES += $$PWD/main.cpp \
           $$PWD/domain/AsocData.cpp \
           $$PWD/domain/BasicColumns.cpp \
           $$PWD/domain/Cell.cpp \
           $$PWD/domain/Column.cpp \
           $$PWD/domain/InputCntColumn.cpp \
           $$PWD/domain/InputDivColumn.cpp \
           $$PWD/domain/OutputAutoSplitColumn.cpp \
           $$PWD/domain/OutputAutoSumColumn.cpp \
           $$PWD/domain/Sheet.cpp \
           $$PWD/persistence/json/JsonPersistence.cpp \
           $$PWD/presentation/qtgui/EditInvoices.cpp \
           $$PWD/presentation/qtgui/ExistingInvoice.cpp \
           $$PWD/presentation/qtgui/MainWindow.cpp \
           $$PWD/presentation/qtgui/NewInvoice.cpp \
           $$PWD/presentation/qtgui/SetupColumn.cpp \
           $$PWD/presentation/qtgui/SetupAutoSplitColumn.cpp \
           $$PWD/presentation/qtgui/SheetModel.cpp \
           $$PWD/presentation/qtgui/TablePrintDialog.cpp

HEADERS += \
           $$PWD/domain/AsocData.h \
           $$PWD/domain/BasicColumns.h \
           $$PWD/domain/Cell.h \
           $$PWD/domain/Column.h \
           $$PWD/domain/commons.h \
           $$PWD/domain/InputCntColumn.h \
           $$PWD/domain/InputDivColumn.h \
           $$PWD/domain/Invoice.h \
           $$PWD/domain/OutputAutoSplitColumn.h \
           $$PWD/domain/OutputAutoSumColumn.h \
           $$PWD/domain/Sheet.h \
           $$PWD/domain/SplitComponent.h \
           $$PWD/persistence/AsocPersistence.h \
           $$PWD/persistence/json/JsonPersistence.h \
           $$PWD/presentation/qtgui/EditInvoices.h \
           $$PWD/presentation/qtgui/ExistingInvoice.h \
           $$PWD/presentation/qtgui/MainWindow.h \
           $$PWD/presentation/qtgui/NewInvoice.h \
           $$PWD/presentation/qtgui/SetupColumn.h \
           $$PWD/presentation/qtgui/SetupAutoSplitColumn.h \
           $$PWD/presentation/qtgui/SheetModel.h \
           $$PWD/presentation/qtgui/TablePrintDialog.h

FORMS += \
         $$PWD/presentation/qtgui/EditInvoices.ui \
         $$PWD/presentation/qtgui/ExistingInvoice.ui \
         $$PWD/presentation/qtgui/MainWindow.ui \
         $$PWD/presentation/qtgui/NewInvoice.ui \
         $$PWD/presentation/qtgui/SetupColumn.ui \
         $$PWD/presentation/qtgui/SetupAutoSplitColumn.ui \
         $$PWD/presentation/qtgui/TablePrintDialog.ui

INCLUDEPATH += $$PWD
