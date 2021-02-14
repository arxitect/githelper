cmake_minimum_required(VERSION 3.10)
set(APP_NAME "githelper")
project(${APP_NAME} LANGUAGES CXX)
include( GNUInstallDirs )

set(TARGET tgt PROPERTY CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
add_definitions(-DROOT_PATH="/usr/${CMAKE_INSTALL_DATADIR}/${APP_NAME}")

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5Sql COMPONENTS REQUIRED)

include_directories(${Qt5Widgets_INCLUDE_DIRS})

set(SOURCE_FILES
        main.cpp
        app/MainWindow.cpp app/MainWindow.h
        app/helpers/Config.cpp app/helpers/Config.h
        app/helpers/DbProxy.cpp app/helpers/DbProxy.h
        app/parts/CommandButton.h)

add_executable(${APP_NAME} ${SOURCE_FILES})

target_link_libraries(${APP_NAME} Qt5::Widgets Qt5::Sql)

install(DIRECTORY assets DESTINATION ${CMAKE_INSTALL_DATADIR}/${APP_NAME})
install(FILES githelperdb DESTINATION ${CMAKE_INSTALL_DATADIR}/${APP_NAME})
install(TARGETS ${APP_NAME}
        RUNTIME DESTINATION
        ${CMAKE_INSTALL_PREFIX}/bin)