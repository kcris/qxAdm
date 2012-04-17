#-------------------------------------------------
#
# Project created by QtCreator 2011-05-16T20:46:23
#
#-------------------------------------------------

QT       += core gui

TARGET = qa
TEMPLATE = app

include(didisoft.pri)
include(core/core.pri)

#link with qjson library
INCLUDEPATH+=../deps
LIBS+= -L../deps/qjson/lib -lqjson0

SOURCES += main.cpp\
        MainWindow.cpp \
    SetupColumn.cpp \
    SetupAutoSplitColumn.cpp \
    EditInvoices.cpp \
    AsocData.cpp \
    TablePrintDialog.cpp

HEADERS  += MainWindow.h \
    SetupColumn.h \
    SetupAutoSplitColumn.h \
    EditInvoices.h \
    AsocData.h \
    TablePrintDialog.h

FORMS    += MainWindow.ui \
    SetupColumn.ui \
    SetupAutoSplitColumn.ui \
    EditInvoices.ui \
    TablePrintDialog.ui

OTHER_FILES += ../var/qa.json

DESTDIR=$$PWD/../bin
