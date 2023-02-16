add_library(halo3lib MODULE
	source/halo3lib_private_pch.h
	source/shell/delta_interface.cpp
	source/game/game_options.cpp
	source/game/game_options.h)

set_common_props(halo3lib)

target_include_directories(halo3lib PRIVATE
	source)

target_precompile_headers(halo3lib PRIVATE
	source/halo3lib_private_pch.h)

target_link_libraries(halo3lib PRIVATE
	common
	gamelib)

target_link_options(halo3lib PRIVATE
	"/OPT:NOREF")

set_target_properties(halo3lib PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${MCC_RUNTIME_OUTPUT_DIRECTORY}/halomods"
	FOLDER "Game Libraries")
