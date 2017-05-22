set(VM_SOURCES_MONO 
    mono_test.cpp
	)
convert_to_absolute_path(VM_SOURCES_MONO ${VM_SOURCES_MONO})

# add_definitions(-DENABLE_MONO)
# add_definitions(-DUNITY_EDITOR)
# add_definitions(-DMONO_2_12)

add_library_clr(mono ${VM_SOURCES_MONO})