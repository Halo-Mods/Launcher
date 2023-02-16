add_library(mcclib MODULE
	game_library_hooks.cpp
	game_library_hooks.h
	dllmain.cpp
	mcclib_private_pch.h)

set_common_props(mcclib)

target_precompile_headers(mcclib PRIVATE
	mcclib_private_pch.h)

target_link_libraries(mcclib PRIVATE
	detourslib
	common)

add_dependencies(mcclib
	halo2lib
	halo3lib)

set_target_properties(mcclib PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${MCC_RUNTIME_OUTPUT_DIRECTORY}/mcc/binaries/win64"
	FOLDER "MCC Projects")
