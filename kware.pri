#
# Copyright (c) 2018, KWare
#

#this file contains common settings for all projects


qMakeSpec = $$(QMAKESPEC)
#message("Qt version=$$QT_VERSION spec=$$qMakeSpec compiler=$$QMAKE_CXX")

SONAME=
win32: SONAME=dll
unix: SONAME=so
mac: SONAME=dylib

#see also QMAKE_EXTENSION_SHLIB, TARGET_EXT
#isEmpty(QMAKE_EXTENSION_SHLIB) {
#  QMAKE_EXTENSION_SHLIB=$$SONAME
#}

#
# get compiler information; we support g++ and msvc2010
#

#detect mingw g++
win32-g++ {
  GCC_MAJ = $$system(echo | gcc -dM -E - | findstr __GNUC__)
  GCC_MIN = $$system(echo | gcc -dM -E - | findstr __GNUC_MINOR__)
  GCC_PL = $$system(echo | gcc -dM -E - | findstr __GNUC_PATCHLEVEL__)
  GCC_VER = $$last(GCC_MAJ)$$last(GCC_MIN)$$last(GCC_PL)
  COMPILER=g++$$GCC_VER
#  message("Compiler (mingw): $$COMPILER")
  QMAKE_CXXFLAGS+=-Wno-unused-function
}

#detect gnu g++
linux-g++* {
  GCC_MAJ = $$system(echo | gcc -dM -E - | fgrep __GNUC__ | cut -d\" \" -f 3)
  GCC_MIN = $$system(echo | gcc -dM -E - | fgrep __GNUC_MINOR__ | cut -d\" \" -f 3)
  GCC_PL  = $$system(echo | gcc -dM -E - | fgrep __GNUC_PATCHLEVEL__ | cut -d\" \" -f 3)
  GCC_VER = $$GCC_MAJ$$GCC_MIN$$GCC_PL
  COMPILER=g++$$GCC_VER
#  message("Compiler (gnu): $$COMPILER")
  QMAKE_CXXFLAGS+=-Wno-unused-function
}

#detect msvc version
contains( qMakeSpec , win32-msvc2010 ) {
  COMPILER="msvc2010"
#  message("Compiler (ms): $$COMPILER")
}


#To compile using Visual Studio, do this:
#1. set QMAKESPEC=win32-msvc2010
#2. qmake -tp vc project.pro
#3. compile generated .vcxproj using Visual Studio

isEmpty(COMPILER) {
    error("Could not detect compiler: $$COMPILER. Aborting")
}

#
# determine full ABI information: arch-os-compiler-config
#
TARGET_ARCH=$$QMAKE_HOST.arch
TARGET_OS=$$QMAKE_HOST.os
TARGET_COMPILER=$${COMPILER}
#TARGET_COMPILER=$$quote($${COMPILER})
TARGET_CFG=
CONFIG(debug, debug|release):TARGET_CFG="debug"
else:TARGET_CFG="release"

#description of the compiled ABI:
ABI=$${TARGET_ARCH}-$${TARGET_OS}-$${TARGET_COMPILER}-$${TARGET_CFG}
message("ABI: $$ABI")

#
# based on current folder and abi, determine useful folder names
#
LIBDIR_NAME="lib-$$ABI" #folder name for output libraries
BINDIR_NAME="bin-$$ABI" #folder name for output executables

MYROOTDIR=$$PWD #current folder shoud be the root repository folder
#message("Root repo dir: $$MYROOTDIR")

top_srcdir=$$PWD
top_builddir=$$shadowed($$PWD)

# intermediary build files go here
BUILDDIR=build/$${TARGET_CFG}

MOC_DIR      = $$BUILDDIR/moc
OBJECTS_DIR  = $$BUILDDIR/obj
RCC_DIR      = $$BUILDDIR/qrc
UI_DIR       = $$BUILDDIR/uic

INCLUDEPATH += $$UI_DIR

#
# common header: platform.h
#
#INCLUDEPATH += $$MYROOTDIR
#HEADERS += $$MYROOTDIR/platform.h

#COMMONS_SRC_DIR="$$MYROOTDIR/Commons/src"
#COMMONS_LIBS_DIR="\"$$MYROOTDIR/Commons/lib/$$LIBDIR_NAME\""

#
# company info/versioning; these interfere with RC_FILE !!!
#
QMAKE_TARGET_COMPANY = KWare
QMAKE_TARGET_COPYRIGHT = Copyright (C) 2009-2018 $$QMAKE_TARGET_COMPANY
DEFINES += "KWARE=\"\\\"$${QMAKE_TARGET_COMPANY}\\\"\""

#
# extract SVN revision number
#

#include($$MYROOTDIR/svn.pri)


#
# enable profiler
#
linux:debug{
PROFILER_FLAGS=-pg #use gprof
QMAKE_CXXFLAGS+=$$PROFILER_FLAGS
QMAKE_LFLAGS+=$$PROFILER_FLAGS
}



#
# debug/release configurations
#
debug {
#DEFINES+=DEBUG
#DEFINES+=_GLIBCXX_DEBUG #enable extra safety checks in c++ standard library (see also _GLIBCXX_DEBUG_PEDANTIC)
}

#
# compiler options
#
QMAKE_CXXFLAGS += -Wall
#QMAKE_CXXFLAGS_DEBUG+=-O0
#QMAKE_CXXFLAGS_RELEASE+=-O2
#CONFIG+=c++11 #QMAKE_CXXFLAGS+=-std=c++11
CONFIG+=c++14 #QMAKE_CXXFLAGS+=-std=c++14




#
# arch specific stuff (spec file should take care of this)
#

linux-g++*:contains(QMAKE_HOST.arch, x86_64):{
    LIBS += -L/usr/lib64
}

#
# to avoid messing with system-wide LD_LIBRARY_PATH on deploy, we can use rpath header at link time
# to reference our custom libdir at startup ($ORIGIN will be the path of the current module)
#

# see https://stackoverflow.com/questions/7506860/qmake-and-passing-origin-to-linker-option-rpath
# see http://qt-project.org/doc/qt-4.8/qmake-variable-reference.html#qmake-lflags-rpath
#
QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN/../lib\''
#QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN/../lib\',-z,origin'


#---------------------------------------------------
#this file contains common settings for *all* projects
#
#DO NOT PUT HERE STUFF THAT IS SPECIFIC TO ONE OR MORE PROJECTS
#BUT ONLY STUFF THAT IS REQUIRED BY ALL PROJECTS
