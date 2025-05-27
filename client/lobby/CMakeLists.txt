cmake_minimum_required(VERSION 3.16)

project(CS2D-LOBBY VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TS_FILES CS2D-LOBBY_es_AR.ts)

set(PROJECT_SOURCES
    src/main.cpp
    src/main_window.cpp
    include/main_window.h
    src/main_window.ui
)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(CS2D-LOBBY
        ${PROJECT_SOURCES}
        resources.qrc
        include/lobby_scene.h
        src/lobby_scene.cpp
        include/welcome_scene.h
        src/welcome_scene.cpp
        include/game_creation_scene.h
        src/game_creation_scene.cpp
        include/styled_button.h
        include/join_game_scene.h
        src/join_game_scene.cpp
    )
target_include_directories(CS2D-LOBBY
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(CS2D-LOBBY PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

include(GNUInstallDirs)
install(TARGETS CS2D-LOBBY
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CS2D-LOBBY)
endif()