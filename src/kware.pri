# Copyright (c) 2011-2013, KWare

#this file contains common settings for all projects


#by switching the following variable, you change the output folders for the binaries
#GCCVER=gcc34
GCCVER=gcc44

PLATF=
mac:    PLATF=mac
win32:  PLATF=win
unix:   PLATF=unix

SONAME=
win32: SONAME=dll
unix: SONAME=so

MAKE=C:/Qt/2010.05/mingw/bin/mingw32-make

#create separate debug/release binaries
CONFIG += debug_and_release
CONFIG(debug, debug|release) {
   mac: TARGET = $$join(TARGET,,,_debug)
   unix: TARGET = $$join(TARGET,,,d)
   win32: TARGET = $$join(TARGET,,,d)
}


#more platform specific tools
win32: MY_COPY_DIR=xcopy /s /q /y /i


# GREAT: since gcc 4.3 we can use the next c++ standard: c++0x
#
# super features like smart pointers (shared_ptr, unique_ptr), static_assert and much more
# are already (2011!) available (see tr1 namespace)
#
# NOTE that a problem arises in gcc/mingw due to some bad headers; it's related to the 'strict ansi' mode of the compiler
# You need to use a patched version of 'cwchar' mingw header: C:\qtsdk\mingw\lib\gcc\mingw32\4.4.0\include\c++\cwchar
# Patched 'cwchar' header simply wraps functions that issue errors in #ifndef __STRICT_ANSI__ ... #endif
# See http://forums.codeblocks.org/index.php?topic=10508.15
#
#don't use QMAKE_CXXFLAGS="-std=c++0x -U__STRICT_ANSI__" since it causes extra issues!?
#don't use QMAKE_CXXFLAGS="-std=c++0x" since it also causes link errors for std::string!?
#use this:
QMAKE_CXXFLAGS="-std=gnu++0x"


#create version info into the binary; these interfere with RC_FILE !!!
QMAKE_TARGET_COMPANY = DidiSoft
QMAKE_TARGET_COPYRIGHT = Copyright (C) 2011 DidiSoft

##see also: $$PWD
