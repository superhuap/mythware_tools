cmake_minimum_required(VERSION 3.31)
project(mythware_tools)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/qt@5/5.15.16_2")

file(GLOB_RECURSE SRC
        "src/*.h"
        "src/*.cpp"
)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED)

add_executable(mythware_tools src/main.cpp ${SRC})

target_include_directories(mythware_tools PRIVATE lib/include)

target_link_directories(mythware_tools PRIVATE lib)

target_link_libraries(mythware_tools
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
        ElaWidgetTools
)

