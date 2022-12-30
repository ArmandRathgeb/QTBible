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

set(HEADER_FILES
        include/MainDisplay.hpp
        include/Tools/WordChart.hpp
        include/Utils/Download.hpp
        include/Dialogs/Settings.hpp
        include/Widgets/TextPane.hpp
        include/Tools/Bible.hpp
        include/Utils/Utils.hpp
        )

set(SRC_FILES
        src/main.cpp
        src/MainDisplay.cpp
        src/Tools/WordChart.cpp
        src/Utils/Download.cpp
        src/Dialogs/Settings.cpp
        src/Widgets/TextPane.cpp
        src/Tools/Bible.cpp
        )

add_executable(QTBible
        ${SRC_FILES}
        ${HEADER_FILES}
        )


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

