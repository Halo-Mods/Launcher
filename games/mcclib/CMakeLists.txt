add_library(mcclib MODULE
	discord_manager.cpp
	discord_manager.h
	steam_manager.cpp
	steam_manager.h
	ufg.cpp
	ufg.h
	dllmain.cpp
	mcclib_private_pch.h)

set_common_props(mcclib)

target_precompile_headers(mcclib PRIVATE
	mcclib_private_pch.h)

target_link_libraries(mcclib PRIVATE
	detourslib
	discordlib
	steamlib
	common
	gamelib)

set_target_properties(mcclib PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${MCC_RUNTIME_OUTPUT_DIRECTORY}/mcc/binaries/win64")
