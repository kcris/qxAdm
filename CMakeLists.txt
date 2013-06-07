#cmake_minimum_required(2.8.8)

project(qxAdm)

# Tell CMake to run moc when necessary:
#set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake to always look for includes there:
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Widgets finds its own dependencies.
#find_package(Qt5Widgets REQUIRED)

#add_executable(qxAdm main.cpp)

#qt5_use_modules(qxAdm Widgets)

#see http://www.kdab.com/using-cmake-with-qt-5/
#see http://doc-snapshot.qt-project.org/5.0/qtdoc/cmake-manual.html
#http://qt-project.org/quarterly/view/using_cmake_to_build_qt_projects


FIND_PACKAGE(Qt4 REQUIRED)

SET(qxAdm_SOURCES 
    src/main.cpp 
    src/MainWindow.cpp
    src/SetupColumn.cpp
    src/SetupAutoSplitColumn.cpp
    src/EditInvoices.cpp
    src/AsocData.cpp
    src/TablePrintDialog.cpp)
SET(qxAdm_HEADERS 
    src/MainWindow.h
    src/SetupColumn.h
    src/SetupAutoSplitColumn.h
    src/EditInvoices.h
    src/AsocData.h
    src/TablePrintDialog.h)
SET(qxAdm_FORMS 
    src/MainWindow.ui
    src/SetupColumn.ui
    src/SetupAutoSplitColumn.ui
    src/EditInvoices.ui
    src/TablePrintDialog.ui)
#SET(qxAdm_RESOURCES qxAdm.qrc)

QT4_WRAP_CPP(qxAdm_HEADERS_MOC ${qxAdm_HEADERS})
QT4_WRAP_UI(qxAdm_FORMS_HEADERS ${qxAdm_FORMS})
QT4_ADD_RESOURCES(qxAdm_RESOURCES_RCC ${qxAdm_RESOURCES})

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

INCLUDE_DIRECTORIES(src)

ADD_EXECUTABLE(qxAdm ${qxAdm_SOURCES} ${qxAdm_HEADERS_MOC} ${qxAdm_FORMS_HEADERS} ${qxAdm_RESOURCES_RCC})
TARGET_LINK_LIBRARIES(qxAdm ${QT_LIBRARIES})
