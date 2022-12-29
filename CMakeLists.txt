cmake_minimum_required(VERSION 3.25)
project(QTBible)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED)
find_package(Qt5Charts REQUIRED)
find_package(KDDockWidgets REQUIRED)

add_executable(QTBible src/main.cpp
        src/Tools/WordChart.cpp
        include/Tools/WordChart.hpp
        src/MainDisplay.cpp
        include/MainDisplay.hpp
        src/Network/Download.cpp
        include/Network/Download.hpp
        src/Dialogs/Settings.cpp include/Dialogs/Settings.hpp src/Widgets/TextPane.cpp include/Widgets/TextPane.hpp src/Tools/Bible.cpp include/Tools/Bible.hpp src/Widgets/ToolPane.cpp include/Widgets/ToolPane.hpp)

configure_file(include/config.h.in config.hpp)

target_precompile_headers(QTBible PRIVATE include/pch.hpp)
target_include_directories(QTBible PRIVATE include)
target_link_libraries(QTBible
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Charts
        Qt5::Network
        KDAB::kddockwidgets
        )

