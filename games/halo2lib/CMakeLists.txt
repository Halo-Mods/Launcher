add_library(halo2lib MODULE
	source/halo2lib_private_pch.h
	source/shell/delta_interface.cpp
	source/main/main_time.cpp
	source/main/main_time.h)

set_common_props(halo2lib)

target_include_directories(halo2lib PRIVATE
	source)

target_precompile_headers(halo2lib PRIVATE
	source/halo2lib_private_pch.h)

target_link_libraries(halo2lib PRIVATE
	common
	gamelib)

target_link_options(halo2lib PRIVATE
	"/OPT:NOREF")

set_target_properties(halo2lib PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${MCC_RUNTIME_OUTPUT_DIRECTORY}/halomods"
	FOLDER "Game Libraries")
