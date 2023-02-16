add_library(gamelib STATIC
	memory/module.cpp
	memory/module.h
	shell/delta_interface.h
	gamelib_public_pch.h
	gamelib_private_pch.h)

set_common_props(gamelib)

target_precompile_headers(gamelib PRIVATE
	gamelib_private_pch.h)

target_link_libraries(gamelib PRIVATE
	detourslib
	common)

set_target_properties(gamelib PROPERTIES
	FOLDER "Game Libraries")
