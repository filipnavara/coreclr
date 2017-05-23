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

add_definitions(-DENABLE_MONO)
add_definitions(-DPLATFORM_STANDALONE)
include_directories(${UNITY_ROOT}/Runtime/Mono)

if(MSVC)
add_definitions(-DUSE_CONSOLEBRANCH_MONO)
endif()
# add_definitions(-DUNITY_EDITOR)
# add_definitions(-DMONO_2_12)

add_library_clr(mono ${VM_SOURCES_MONO})