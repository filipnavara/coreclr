set(VM_SOURCES_MONO 
    mono_coreclr.cpp
    MonoObjectRef.cpp
	)
convert_to_absolute_path(VM_SOURCES_MONO ${VM_SOURCES_MONO})

if ("${UNITY_ROOT}" STREQUAL "")
    set(UNITY_ROOT "$ENV{UNITY_ROOT}")
endif()

if ("${UNITY_ROOT}" STREQUAL "")
    message(FATAL_ERROR "UNITY_ROOT is not provided")
endif()

message("Using Unity: ${UNITY_ROOT}")

add_definitions(-DENABLE_MONO=1)
add_definitions(-DPLATFORM_STANDALONE=1)

if(WIN32)
  add_definitions(-DPLATFORM_WIN=1)
endif()

if(CLR_CMAKE_PLATFORM_DARWIN)
  add_definitions(-DPLATFORM_OSX=1)
endif()

include_directories(${UNITY_ROOT}/Runtime/Mono)

add_library_clr(mono ${VM_SOURCES_MONO})
target_compile_features(mono PRIVATE cxx_range_for)