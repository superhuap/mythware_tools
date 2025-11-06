cmake_minimum_required(VERSION 3.20)

if(WIN32)
    set(DETECTED_PLATFORM "WIN32")
elseif(APPLE)
    set(DETECTED_PLATFORM "APPLE")
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

set(TARGET_PLATFORM ${DETECTED_PLATFORM} CACHE STRING "Target platform: WIN32 or APPLE")
set_property(CACHE TARGET_PLATFORM PROPERTY STRINGS "WIN32" "APPLE")

if(NOT TARGET_PLATFORM STREQUAL DETECTED_PLATFORM)
    message(WARNING "TARGET_PLATFORM=${TARGET_PLATFORM} does not match detected ${DETECTED_PLATFORM}.")
endif()

project(mythware_tools)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(TARGET_PLATFORM STREQUAL "WIN32")
    set(TARGET_ARCH "64" CACHE STRING "Target architecture: 32 or 64")    #此处设置位数
    set_property(CACHE TARGET_ARCH PROPERTY STRINGS "32" "64")

    set(QT_RUNTIME "MD" CACHE STRING "MSVC Runtime: MD (dynamic) or MT (static)") # 此处设置静态还是动态
    set_property(CACHE QT_RUNTIME PROPERTY STRINGS "MD" "MT")

    if(QT_RUNTIME STREQUAL "MT")
        set(QT_SUBDIR "msvc2022_${TARGET_ARCH}_static")
    else()
        set(QT_SUBDIR "msvc2022_${TARGET_ARCH}")
    endif()

    set(DEFAULT_QT_ROOT "E:/envs/Qt/5.15.17/${QT_SUBDIR}")
    set(QT_ROOT "${DEFAULT_QT_ROOT}" CACHE PATH "Qt installation root directory")
    set(CMAKE_PREFIX_PATH "${QT_ROOT}")

    if(QT_RUNTIME STREQUAL "MT")
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")              # /MT
    else()
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")           # /MD
    endif()

elseif(TARGET_PLATFORM STREQUAL "APPLE")

    set(TARGET_ARCH "64")
    set(QT_RUNTIME "MD")

    set(QT_ROOT "/opt/homebrew/opt/qt@5" CACHE PATH "Qt installation root directory")
    set(CMAKE_PREFIX_PATH "${QT_ROOT}")

    set(CMAKE_MACOSX_RPATH ON)

else()
    message(FATAL_ERROR "Unsupported TARGET_PLATFORM: ${TARGET_PLATFORM}")
endif()

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

target_include_directories(${PROJECT_NAME} PRIVATE lib/include)

if(TARGET_PLATFORM STREQUAL "WIN32")
    if(QT_RUNTIME STREQUAL "MT")
        target_link_directories(${PROJECT_NAME} PRIVATE lib/windows/lib)   # 静态库路径
    else()
        target_link_directories(${PROJECT_NAME} PRIVATE lib/windows/dll)   # 动态导入库路径
    endif()
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)

elseif(TARGET_PLATFORM STREQUAL "APPLE")
    target_link_directories(${PROJECT_NAME} PRIVATE lib/macos)             # macOS 库路径
endif()

if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES 
        WIN32_EXECUTABLE TRUE
        LINK_FLAGS "/SUBSYSTEM:WINDOWS"
    )
endif()

target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
        Qt5::Xml
        ElaWidgetTools
)

if(TARGET_PLATFORM STREQUAL "WIN32" AND QT_RUNTIME STREQUAL "MD")
    file(COPY "lib/windows/dll/ElaWidgetTools.dll" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "${QT_ROOT}/bin/windeployqt" "$<TARGET_FILE:${PROJECT_NAME}>"
            COMMENT "Running windeployqt to deploy Qt libraries..."
            VERBATIM
    )
endif()