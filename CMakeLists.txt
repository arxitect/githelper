cmake_minimum_required(VERSION 3.17)
set(APP_NAME "Git-Helper")
project(${APP_NAME} LANGUAGES CXX)

set(TARGET tgt PROPERTY CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5Sql COMPONENTS REQUIRED)

include_directories(${Qt5Widgets_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp)
add_executable(${APP_NAME} ${SOURCE_FILES})

target_link_libraries(${APP_NAME} Qt5::Widgets Qt5::Sql)