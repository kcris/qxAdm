cmake_minimum_required(2.8.8)

project(qxAdm)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Widgets finds its own dependencies.
find_package(Qt5Widgets REQUIRED)

add_executable(qxAdm main.cpp)

qt5_use_modules(qxAdm Widgets)

#see http://www.kdab.com/using-cmake-with-qt-5/

