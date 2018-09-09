#-------------------------------------------------
#
# Project created by QtCreator 2011-05-16T20:46:23
#
#-------------------------------------------------
QT += core gui widgets printsupport

TARGET = qxAdm
TEMPLATE = app

include(kware.pri)
include(src/src.pri)
include(external/external.pri)

OTHER_FILES += var/qa.json
OTHER_FILES += CMakeLists.txt

DESTDIR=$$PWD/bin/$$BINDIR_NAME

INCLUDEPATH += $$PWD
