cmake_minimum_required(VERSION 3.20)

set(VCPKG_TARGET_TRIPLET "x64-windows-static")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

project(mythware_tools)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_compile_options(/utf-8)

find_package(Qt5 REQUIRED COMPONENTS
        Core
        Gui
        Widgets
        Network
        Xml
)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
        "src/*.h"
        "src/*.cpp"
)

add_executable(${PROJECT_NAME} main.cpp ${SRC})

set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE ON)

target_include_directories(${PROJECT_NAME} PRIVATE lib/include)

target_link_directories(${PROJECT_NAME} PRIVATE lib)

target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
        Qt5::Xml
        ElaWidgetTools
)