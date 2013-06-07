cmake_minimum_required(2.8.7)

project(qxAdm)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Widgets finds its own dependencies (QtGui and QtCore).
find_package(Qt5Widgets REQUIRED)

# The Qt5Widgets_INCLUDES also includes the include directories for dependencies QtCore and QtGui
include_directories(${Qt5Widgets_INCLUDES})

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS})

# Executables fail to build with Qt 5 in the default configuration without -fPIE. We add that here.
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

add_executable(qxAdm main.cpp)

# The Qt5Widgets_LIBRARIES variable also includes QtGui and QtCore
target_link_libraries(qxAdm ${Qt5Widgets_LIBRARIES})


#
#see http://www.kdab.com/using-cmake-with-qt-5/
#
