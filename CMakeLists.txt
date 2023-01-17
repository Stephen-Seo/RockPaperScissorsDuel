project(RockPaperScissorsDuelNative)
cmake_minimum_required(VERSION 3.18.4)

set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_C_FLAGS_DEBUG "-O0 -g")
set(CMAKE_C_FLAGS_RELEASE "-O3 -D NDEBUG")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -D NDEBUG")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Debug', none was specified.")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

set(RPSDuelNative_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/basic_renderer.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ems.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/helpers.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d_renderer.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/constants.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/obj.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/a3f.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/a3f_conv.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/qm.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anim_concurrent.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anim_sequence.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anim_model_shrink.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anim_model_grow.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anim_model_attack.cc"
)

set(RPSDuelNative_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ems.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/constants.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/helpers.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/game_renderer.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/basic_renderer.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d_renderer.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/obj.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/a3f.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/a3f_conv.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/qm.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anims.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anim_sequence.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anim_model_shrink.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anim_model_grow.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anim_model_attack.h"
)

add_executable(RPSDuelNative ${RPSDuelNative_SOURCES})

target_link_libraries(RPSDuelNative PUBLIC
    raylib
)

if(EXISTS /usr/bin/clang-format)
    add_custom_target(
        ClangFormatTarget
        COMMAND clang-format -i --style=google ${RPSDuelNative_SOURCES} ${RPSDuelNative_HEADERS}
    )
    add_dependencies(RPSDuelNative ClangFormatTarget)
    message(STATUS "Enabled clang-format formatting.")
endif()
