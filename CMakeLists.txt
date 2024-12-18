cmake_minimum_required(VERSION 3.18.4)
project(RockPaperScissorsDuelNative)

add_compile_options(-Wall -Wextra -Wpedantic
    $<$<CONFIG:DEBUG>:-O0>
)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Debug', none was specified.")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

set(RPSDuelNative_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ems.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/helpers.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d_renderer.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/constants.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/obj.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/arrays.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/arrays_conv.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/qm.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anims.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anim_concurrent.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anim_sequence.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anim_model_shrink.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anim_model_grow.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anim_model_attack.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anim_model_still.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anim_falling_2d.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/deferred_2d_draw.cc"
)

set(RPSDuelNative_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ems.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/constants.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/helpers.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/game_renderer.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d_renderer.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/obj.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/arrays.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/arrays_conv.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/qm.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anims.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anim_concurrent.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anim_sequence.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anim_model_shrink.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anim_model_grow.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anim_model_attack.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anim_model_still.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/anim_falling_2d.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/3d/deferred_2d_draw.h"
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
