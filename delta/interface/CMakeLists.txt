add_executable(interface WIN32
	main.cpp
	interface_private_pch.h)

set_common_props(interface)

target_precompile_headers(interface PRIVATE
	interface_private_pch.h)

target_link_libraries(interface PRIVATE
	ultralightlibs
	common)

add_dependencies(interface
	halo2lib
	halo3lib
	copy_ultralight_dlls)

set_target_properties(interface PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${MCC_RUNTIME_OUTPUT_DIRECTORY}/halomods"
	FOLDER "Delta Projects")
