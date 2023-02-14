cmake_path(GET CMAKE_CXX_COMPILER PARENT_PATH EP_VS_TOOLS_DIR)
set(NMAKE_EXE "${EP_VS_TOOLS_DIR}/nmake.exe")

set(EP_DETOURS "Detours")
ExternalProject_Add(
	${EP_DETOURS}
	
	PREFIX				${EP_DETOURS}
	URL					https://github.com/microsoft/Detours/archive/refs/heads/main.zip
	#GIT_REPOSITORY		https://github.com/microsoft/Detours
	#GIT_BRANCH			main
	
	SOURCE_DIR			"${CMAKE_CURRENT_BINARY_DIR}/${EP_DETOURS}Source"
	BINARY_DIR			"${CMAKE_CURRENT_BINARY_DIR}/${EP_DETOURS}Source"
	INSTALL_DIR			""

	CONFIGURE_COMMAND	""
	UPDATE_COMMAND		""
	INSTALL_COMMAND		""

	BUILD_ALWAYS		OFF
	BUILD_COMMAND		${NMAKE_EXE} /F <SOURCE_DIR>/Makefile DETOURS_CONFIG=Release DETOURS_WIN_7=1 all
	COMMAND				${CMAKE_COMMAND} -E copy <SOURCE_DIR> <INSTALL_DIR>/detours.lib)

add_library(detourslib STATIC IMPORTED)
add_dependencies(detourslib PRIVATE ${EP_DETOURS})
ExternalProject_Get_property(${EP_DETOURS} SOURCE_DIR)
set_target_properties(detourslib PROPERTIES
	IMPORTED_LOCATION "${SOURCE_DIR}/lib.x64Release/detours.lib"
	INTERFACE_INCLUDE_DIRECTORIES "${SOURCE_DIR}/include")

set(EP_DISCORD "Discord")
ExternalProject_Add(
	${EP_DISCORD}
	
	PREFIX				${EP_DISCORD}
	URL					https://dl-game-sdk.discordapp.net/3.2.1/discord_game_sdk.zip
	
	SOURCE_DIR			"${CMAKE_CURRENT_BINARY_DIR}/${EP_DISCORD}Source"
	BINARY_DIR			""
	INSTALL_DIR			""

	CONFIGURE_COMMAND	""
	UPDATE_COMMAND		""
	INSTALL_COMMAND		""
	BUILD_COMMAND		"")

add_library(discordlib SHARED IMPORTED)
add_dependencies(discordlib PRIVATE ${EP_DISCORD})
ExternalProject_Get_property(${EP_DISCORD} SOURCE_DIR)
set_target_properties(discordlib PROPERTIES
	IMPORTED_LOCATION "${SOURCE_DIR}/lib/x86_64/discord_game_sdk.dll.lib"
	IMPORTED_IMPLIB "${SOURCE_DIR}/lib/x86_64/discord_game_sdk.dll"
	INTERFACE_INCLUDE_DIRECTORIES "${SOURCE_DIR}/c")

if (NOT DEFINED STEAMWORKS_SDK)
	message(FATAL_ERROR "You need to point STEAMWORKS_SDK to the Steamworks SDK")
endif()

add_library(steamlib SHARED IMPORTED)
set_target_properties(steamlib PROPERTIES
	IMPORTED_LOCATION "${STEAMWORKS_SDK}/redistributable_bin/win64/steam_api64.dll"
	IMPORTED_IMPLIB "${STEAMWORKS_SDK}/redistributable_bin/win64/steam_api64.lib"
	INTERFACE_INCLUDE_DIRECTORIES "${STEAMWORKS_SDK}/public")
