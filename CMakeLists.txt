cmake_minimum_required(VERSION 3.5)

project(XO LANGUAGES CXX)

find_package(Qt5 5.13.1 COMPONENTS Widgets  Core Network  REQUIRED)

get_target_property(QtCore_location Qt5::Core LOCATION)
get_target_property(QtNetwork_location Qt5::Network LOCATION)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_USE_QTNETWORK true)


add_executable(XO
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  win.cpp
  win.h
  qpushbuttonid.cpp
  qpushbuttonid.h
  resource.grc
)

target_link_libraries(XO PRIVATE Qt5::Widgets)
target_link_libraries(XO PRIVATE Qt5::Core)
target_link_libraries(XO PRIVATE Qt5::Network)
