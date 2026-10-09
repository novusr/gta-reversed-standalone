# Minimal standalone test for librw integration validation
cmake_minimum_required(VERSION 3.20)
project(test_librw CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define standalone mode
add_compile_definitions(NOTSA_STANDALONE_NATIVE)
add_compile_definitions(NOTSA_STANDALONE)

# Configure librw for GL3/SDL3
if (NOT LIBRW_PLATFORM)
    if (WIN32)
        set(LIBRW_PLATFORM "D3D9" CACHE STRING "librw platform" FORCE)
    else()
        set(LIBRW_PLATFORM "GL3" CACHE STRING "librw platform" FORCE)
    endif()
endif()
if (LIBRW_PLATFORM STREQUAL "GL3")
    set(LIBRW_GL3_GFXLIB "GLFW" CACHE STRING "librw GL3 gfxlib" FORCE)
endif()
set(LIBRW_TOOLS OFF CACHE BOOL "Build librw tools" FORCE)
set(LIBRW_INSTALL OFF CACHE BOOL "Install librw files" FORCE)
set(LIBRW_EXAMPLES OFF CACHE BOOL "Build librw examples" FORCE)

# Add librw
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../vendor/librw" "${CMAKE_BINARY_DIR}/librw")

# Source files needed for the test
set(GAME_SA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../source/game_sa")

add_executable(test_librw
    test_librw.cpp
    ${GAME_SA_DIR}/RenderWare/rw/rwplcore.cpp
    ${GAME_SA_DIR}/RenderWare/rw/rwcore.cpp
    ${GAME_SA_DIR}/RenderWare/rw/rpworld.cpp
    ${GAME_SA_DIR}/RenderWare/rw/rtanim.cpp
)

target_include_directories(test_librw PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../source
    ${CMAKE_CURRENT_SOURCE_DIR}/../source/game_sa
    ${CMAKE_CURRENT_SOURCE_DIR}/../source/game_sa/RenderWare
    ${CMAKE_CURRENT_SOURCE_DIR}/../source/game_sa/RenderWare/rw
    ${CMAKE_CURRENT_SOURCE_DIR}/../source/game_sa/Pipelines
    ${CMAKE_CURRENT_SOURCE_DIR}/../source/game_sa/Pipelines/CustomBuilding
    ${CMAKE_CURRENT_SOURCE_DIR}/../source/game_sa/Pipelines/CustomCarEnvMap
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/librw
)

# Link librw
if (TARGET librw::librw)
    target_link_libraries(test_librw PRIVATE librw::librw)
elseif (TARGET librw)
    target_link_libraries(test_librw PRIVATE librw)
endif()

# OpenGL on Linux
if (NOT WIN32)
    find_package(OpenGL QUIET)
    if (TARGET OpenGL::OpenGL)
        target_link_libraries(test_librw PRIVATE OpenGL::OpenGL)
    elseif (TARGET OpenGL::GL)
        target_link_libraries(test_librw PRIVATE OpenGL::GL)
    endif()
endif()

find_package(fmt QUIET)
if (TARGET fmt::fmt)
    target_link_libraries(test_librw PRIVATE fmt::fmt)
else()
    find_library(FMT_LIB fmt)
    if (FMT_LIB)
        target_link_libraries(test_librw PRIVATE ${FMT_LIB})
    else()
        target_compile_definitions(test_librw PRIVATE FMT_HEADER_ONLY=1)
    endif()
endif()

# Suppress warnings from thunk code in non-standalone paths
target_compile_options(test_librw PRIVATE
    -Wno-switch -Wno-unused-parameter -Wno-return-type
    -Wno-missing-field-initializers -Wno-write-strings
)
