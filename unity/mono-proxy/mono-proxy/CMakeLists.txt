# Require at least version 2.8.12 of CMake
cmake_minimum_required(VERSION 2.8.12)

project(mono)

file(GLOB PROJECT_SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)


if ("${UNITY_ROOT}" STREQUAL "")
    set(UNITY_ROOT "$ENV{UNITY_ROOT}")
endif()

if ("${UNITY_ROOT}" STREQUAL "")
    message(FATAL_ERROR "UNITY_ROOT is not provided")
endif()

add_definitions(-DENABLE_MONO)
add_definitions(-DPLATFORM_STANDALONE)
add_definitions(-DPLATFORM_WIN)
add_definitions(-DENABLE_MONO_MEMORY_PROFILER)
include_directories(${UNITY_ROOT}/Runtime/Mono)

add_library(mono SHARED ${PROJECT_SRC_FILES})

