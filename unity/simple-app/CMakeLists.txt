# Require at least version 2.8.12 of CMake
cmake_minimum_required(VERSION 2.8.12)

set(PROJECT_NAME_STR mono_test_app)
project(${PROJECT_NAME_STR} CXX)

if ("${UNITY_ROOT}" STREQUAL "")
    set(UNITY_ROOT "$ENV{UNITY_ROOT}")
endif()

if ("${UNITY_ROOT}" STREQUAL "")
    message(FATAL_ERROR "UNITY_ROOT is not provided")
endif()

message("Using Unity: ${UNITY_ROOT}")

file(GLOB PROJECT_SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)

include_directories(${UNITY_ROOT}/Runtime/Mono)
include_directories(${UNITY_ROOT}/External/MonoBleedingEdge)
include_directories(${CLR_DIR}/src/inc)

if(MSVC)
add_definitions(-DUSE_CONSOLEBRANCH_MONO)
endif()

add_executable(${PROJECT_NAME_STR} ${PROJECT_SRC_FILES})
target_compile_features(${PROJECT_NAME_STR} PRIVATE cxx_range_for)
target_compile_definitions(${PROJECT_NAME_STR} PRIVATE ENABLE_MONO=1 PLATFORM_STANDALONE=1)
