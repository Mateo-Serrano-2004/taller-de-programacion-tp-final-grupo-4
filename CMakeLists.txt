cmake_minimum_required(VERSION 3.24)

if (POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

set(CMAKE_CXX_EXTENSIONS ON)

project(counter_strike_2d
    VERSION 1.0
    HOMEPAGE_URL "https://github.com/URL-HERE"
    LANGUAGES CXX
    )

option(CS2D_TESTS "Enable / disable tests." OFF)
option(CS2D_CLIENT "Enable / disable client program." ON)
option(CS2D_SERVER "Enable / disable server program." ON)
option(CS2D_EDITOR "Enable / disable editor program." OFF)
option(CS2D_MAKE_WARNINGS_AS_ERRORS "Enable / disable warnings as errors." OFF)

message(CMAKE_CXX_COMPILER_ID="${CMAKE_CXX_COMPILER_ID}")

add_library(cs2d_common STATIC)
set_target_properties(cs2d_common PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(common/)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(cs2d_common ${CS2D_MAKE_WARNINGS_AS_ERRORS} FALSE)

target_include_directories(cs2d_common PUBLIC .)

if(CS2D_CLIENT OR CS2D_EDITOR)
    set(SDL2PP_WITH_IMAGE YES)
    set(SDL2PP_WITH_MIXER YES)
    set(SDL2PP_WITH_TTF YES)

    include(FetchContent)

    FetchContent_Declare(
        libSDL2pp
        OVERRIDE_FIND_PACKAGE
        URL https://github.com/libSDL2pp/libSDL2pp/archive/cc198c9a5657048bee67ece82de620b2d5661084.zip
    )

    FetchContent_MakeAvailable(libSDL2pp)
endif()

# Program section
# ---------------
if(CS2D_CLIENT)
    find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)

    add_executable(cs2d_client)

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_definitions(cs2d_client PRIVATE DEBUG_MODE)
    endif()

    add_dependencies(cs2d_client cs2d_common SDL2pp::SDL2pp)

    add_subdirectory(client/)

    set_project_warnings(cs2d_client ${CS2D_MAKE_WARNINGS_AS_ERRORS} FALSE)

    target_include_directories(cs2d_client PRIVATE ${CMAKE_SOURCE_DIR})
    target_include_directories(cs2d_client PRIVATE ${libSDL2pp_SOURCE_DIR})
    target_include_directories(cs2d_client PRIVATE ${Qt${QT_VERSION_MAJOR}_INCLUDE_DIRS})

    target_link_libraries(cs2d_client cs2d_common SDL2pp::SDL2pp Qt${QT_VERSION_MAJOR}::Widgets)
endif()

if(CS2D_SERVER)
    add_executable(cs2d_server)
    add_dependencies(cs2d_server cs2d_common)
    add_subdirectory(server/)

    set_project_warnings(cs2d_server ${CS2D_MAKE_WARNINGS_AS_ERRORS} FALSE)

    target_link_libraries(cs2d_server cs2d_common)
endif()

if(CS2D_EDITOR)
    add_executable(cs2d_editor)
    add_dependencies(cs2d_editor)
    add_subdirectory(editor/)

    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set_project_warnings(cs2d_editor ${CS2D_MAKE_WARNINGS_AS_ERRORS} FALSE)

    #target_include_directories(cs2d_editor PRIVATE ${libSDL2pp_SOURCE_DIR})

    target_link_libraries(cs2d_editor cs2d_common Qt5::Widgets)
endif()


# Testing section
# ---------------

if(CS2D_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)

    add_executable(cs2d_tests)
    add_dependencies(cs2d_tests cs2d_common)

    target_include_directories(cs2d_tests PUBLIC .)

    add_subdirectory(tests/)

    set_project_warnings(cs2d_tests ${CS2D_MAKE_WARNINGS_AS_ERRORS} TRUE)

    target_include_directories(cs2d_tests
        PUBLIC
        ${gtest_SOURCE_DIR}/include
        ${gmock_SOURCE_DIR}/include
        )

    target_link_libraries(cs2d_tests
        cs2d_common
        GTest::gtest_main
    )
endif()
