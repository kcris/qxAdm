#-------------------------------------------------
#
# Project created by QtCreator 2011-05-16T20:46:23
#
#-------------------------------------------------

QT       += core gui

TARGET = qa
TEMPLATE = app

include(didisoft.pri)
include(core.pri)

SOURCES += main.cpp\
        MainWindow.cpp \
    SetupColumn.cpp \
    SetupAutoSplitColumn.cpp \
    EditInvoices.cpp

HEADERS  += MainWindow.h \
    SetupColumn.h \
    SetupAutoSplitColumn.h \
    EditInvoices.h

FORMS    += MainWindow.ui \
    SetupColumn.ui \
    SetupAutoSplitColumn.ui \
    EditInvoices.ui
