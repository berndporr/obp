cmake_minimum_required(VERSION 3.8.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(obp)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# required packages
find_package(Qt5 COMPONENTS Widgets PrintSupport Core REQUIRED)
find_package(Threads)

# required libraries
# find_library(comedi REQUIRED)
# find_library(iir REQUIRED)
# find_library(qwt REQUIRED)

set(PROJECT_LIBS
      Threads
      comedi
      iir)

# add thrid party include directory
include_directories(3rdParty/plog/include)

add_executable(obp
        main.cpp
        Window.cpp
        Plot.cpp
        Processing.cpp
        ComediHandler.cpp
        Datarecord.cpp
        OBPDetection.cpp
        IObserver.h
        ISubject.h
        InfoDialog.cpp
        SettingsDialog.cpp
        common.h)

target_link_libraries(obp Qt5::Widgets Qt5::PrintSupport Qt5::Core comedi iir qwt-qt5 ${CMAKE_THREAD_LIBS_INIT})

include(CTest) # automatically calls enable_testing()
add_subdirectory(tests)
