cmake_minimum_required(VERSION 3.1)

project(qxAdm)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#see:
#http://www.kdab.com/using-cmake-with-qt-5/
#http://doc.qt.io/qt-5/cmake-manual.html
#http://qt-project.org/quarterly/view/using_cmake_to_build_qt_projects

#
# qt5 support:
#
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 COMPONENTS Widgets PrintSupport)
#find_package(Qt5Widgets REQUIRED)
#find_package(Qt5PrintSupport REQUIRED)

SET(qxAdm_SOURCES 
    src/main.cpp 
    src/domain/AsocData.cpp 
    src/domain/BasicColumns.cpp
    src/domain/Cell.cpp
    src/domain/Column.cpp
    src/domain/InputCntColumn.cpp
    src/domain/InputDivColumn.cpp
    src/domain/OutputAutoSplitColumn.cpp
    src/domain/OutputAutoSumColumn.cpp
    src/domain/Sheet.cpp
    src/persistence/json/JsonPersistence.cpp
    src/presentation/qtgui/EditInvoices.cpp
    src/presentation/qtgui/ExistingInvoice.cpp
    src/presentation/qtgui/MainWindow.cpp
    src/presentation/qtgui/NewInvoice.cpp
    src/presentation/qtgui/SetupColumn.cpp
    src/presentation/qtgui/SetupAutoSplitColumn.cpp
    src/presentation/qtgui/SheetModel.cpp
    src/presentation/qtgui/TablePrintDialog.cpp
)

SET(qxAdm_HEADERS 
    src/domain/AsocData.h
    src/domain/BasicColumns.h
    src/domain/Cell.h
    src/domain/Column.h
    src/domain/commons.h
    src/domain/InputCntColumn.h
    src/domain/InputDivColumn.h
    src/domain/Invoice.h
    src/domain/OutputAutoSplitColumn.h
    src/domain/OutputAutoSumColumn.h
    src/domain/Sheet.h
    src/domain/SplitComponent.h
    src/persistence/AsocPersistence.h
    src/persistence/json/JsonPersistence.h
    src/presentation/qtgui/EditInvoices.h
    src/presentation/qtgui/ExistingInvoice.h
    src/presentation/qtgui/MainWindow.h
    src/presentation/qtgui/NewInvoice.h
    src/presentation/qtgui/SetupColumn.h
    src/presentation/qtgui/SetupAutoSplitColumn.h
    src/presentation/qtgui/SheetModel.h
    src/presentation/qtgui/TablePrintDialog.h
    external/gtest/FloatingPoint.h
    external/uuid/uuid.h
)

SET(qxAdm_FORMS 
    src/presentation/qtgui/EditInvoices.ui
    src/presentation/qtgui/ExistingInvoice.ui
    src/presentation/qtgui/MainWindow.ui
    src/presentation/qtgui/NewInvoice.ui
    src/presentation/qtgui/SetupColumn.ui
    src/presentation/qtgui/SetupAutoSplitColumn.ui
    src/presentation/qtgui/TablePrintDialog.ui
)

#SET(qxAdm_RESOURCES qxAdm.qrc)

QT5_WRAP_UI(UIS_HDRS ${qxAdm_FORMS})

add_executable(qxAdm ${qxAdm_SOURCES} ${UIS_HDRS})

qt5_use_modules(qxAdm Core)
qt5_use_modules(qxAdm Widgets)
qt5_use_modules(qxAdm PrintSupport)

target_include_directories(qxAdm PRIVATE . src)

target_link_libraries(qxAdm)

#target_link_libraries(qxAdm Qt5::Widgets Qt5::PrintSupport)
