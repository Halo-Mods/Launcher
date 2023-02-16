cmake_path(GET CMAKE_CXX_COMPILER PARENT_PATH EP_VS_TOOLS_DIR)
set(NMAKE_EXE "${EP_VS_TOOLS_DIR}/nmake.exe")

set(EP_DETOURS "Detours")
ExternalProject_Add(
	${EP_DETOURS}
	
	PREFIX				${EP_DETOURS}
	URL					https://github.com/microsoft/Detours/archive/refs/heads/main.zip
	
	SOURCE_DIR			"${CMAKE_CURRENT_BINARY_DIR}/${EP_DETOURS}Source"
	BINARY_DIR			"${CMAKE_CURRENT_BINARY_DIR}/${EP_DETOURS}Source"
	INSTALL_DIR			""

	CONFIGURE_COMMAND	""
	UPDATE_COMMAND		""
	INSTALL_COMMAND		""

	BUILD_ALWAYS		OFF
	BUILD_COMMAND		${NMAKE_EXE} /F <SOURCE_DIR>/Makefile DETOURS_CONFIG=Release DETOURS_WIN_7=1 all
	COMMAND				${CMAKE_COMMAND} -E copy <SOURCE_DIR> <INSTALL_DIR>/detours.lib)

add_library(detourslib STATIC IMPORTED GLOBAL)
add_dependencies(detourslib PRIVATE ${EP_DETOURS})
ExternalProject_Get_property(${EP_DETOURS} SOURCE_DIR)
set_target_properties(detourslib PROPERTIES
	IMPORTED_LOCATION				"${SOURCE_DIR}/lib.x64Release/detours.lib"
	INTERFACE_INCLUDE_DIRECTORIES	"${SOURCE_DIR}/include")

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

add_library(discordlib SHARED IMPORTED GLOBAL)
add_dependencies(discordlib PRIVATE ${EP_DISCORD})
ExternalProject_Get_property(${EP_DISCORD} SOURCE_DIR)
set_target_properties(discordlib PROPERTIES
	IMPORTED_IMPLIB					"${SOURCE_DIR}/lib/x86_64/discord_game_sdk.dll.lib"
	IMPORTED_LOCATION				"${SOURCE_DIR}/lib/x86_64/discord_game_sdk.dll"
	INTERFACE_INCLUDE_DIRECTORIES	"${SOURCE_DIR}/c")

if (NOT DEFINED STEAMWORKS_SDK)
	message(FATAL_ERROR "You need to point STEAMWORKS_SDK to the Steamworks SDK")
endif()
add_library(steamlib SHARED IMPORTED GLOBAL)
set_target_properties(steamlib PROPERTIES
	IMPORTED_LOCATION				"${STEAMWORKS_SDK}/redistributable_bin/win64/steam_api64.dll"
	IMPORTED_IMPLIB					"${STEAMWORKS_SDK}/redistributable_bin/win64/steam_api64.lib"
	INTERFACE_INCLUDE_DIRECTORIES	"${STEAMWORKS_SDK}/public")

set(EP_ULTRALIGHT "Ultralight")
ExternalProject_Add(
	${EP_ULTRALIGHT}
	
	PREFIX				${EP_ULTRALIGHT}
	URL					https://ultralight-sdk.sfo2.cdn.digitaloceanspaces.com/ultralight-sdk-latest-win-x64.7z
	
	SOURCE_DIR			"${CMAKE_CURRENT_BINARY_DIR}/${EP_ULTRALIGHT}Source"
	BINARY_DIR			""
	INSTALL_DIR			""

	CONFIGURE_COMMAND	""
	UPDATE_COMMAND		""
	INSTALL_COMMAND		""
	BUILD_COMMAND		"")
ExternalProject_Get_property(${EP_ULTRALIGHT} SOURCE_DIR)

# In the future we will use the min build of Ultralight 1.3 to avoid including video playback dependencies
set(webcore_LIBRARIES
	"${SOURCE_DIR}/bin/gmodule-2.0-0.dll"
	"${SOURCE_DIR}/bin/gthread-2.0-0.dll"
	"${SOURCE_DIR}/bin/gio-2.0-0.dll"
	"${SOURCE_DIR}/bin/glib-2.0-0.dll"
	"${SOURCE_DIR}/bin/gobject-2.0-0.dll"
	"${SOURCE_DIR}/bin/gstreamer-full-1.0.dll")

add_library(webcorelib SHARED IMPORTED GLOBAL)
add_dependencies(webcorelib PRIVATE ${EP_ULTRALIGHT})
set(webcore_DLL "${SOURCE_DIR}/bin/WebCore.dll")
set_target_properties(webcorelib PROPERTIES
	IMPORTED_IMPLIB					"${SOURCE_DIR}/lib/WebCore.lib"
	IMPORTED_LOCATION				"${webcore_DLL}")

add_library(ultralightcorelib SHARED IMPORTED GLOBAL)
add_dependencies(ultralightcorelib PRIVATE ${EP_ULTRALIGHT})
set(ultralightcore_DLL "${SOURCE_DIR}/bin/UltralightCore.dll")
set_target_properties(ultralightcorelib PROPERTIES
	IMPORTED_IMPLIB					"${SOURCE_DIR}/lib/UltralightCore.lib"
	IMPORTED_LOCATION				"${ultralightcore_DLL}")

add_library(ultralightlib SHARED IMPORTED GLOBAL)
add_dependencies(ultralightlib PRIVATE ${EP_ULTRALIGHT})
set(ultralight_DLL "${SOURCE_DIR}/bin/Ultralight.dll")
set_target_properties(ultralightlib PROPERTIES
	IMPORTED_IMPLIB					"${SOURCE_DIR}/lib/Ultralight.lib"
	IMPORTED_LOCATION				"${ultralight_DLL}")
target_link_libraries(ultralightlib INTERFACE
	webcorelib
	ultralightcorelib)

add_library(appcore SHARED IMPORTED GLOBAL)
add_dependencies(appcore PRIVATE ${EP_ULTRALIGHT})
set(appcore_DLL "${SOURCE_DIR}/bin/AppCore.dll")
set_target_properties(appcore PROPERTIES
	IMPORTED_IMPLIB					"${SOURCE_DIR}/lib/AppCore.lib"
	IMPORTED_LOCATION				"${appcore_DLL}")
target_link_libraries(appcore INTERFACE
	ultralightlib)

add_library(ultralightlibs INTERFACE)
target_include_directories(ultralightlibs INTERFACE
	"${SOURCE_DIR}/include")
target_link_libraries(ultralightlibs INTERFACE
	ultralightlib)

add_custom_target(copy_ultralight_dlls
	${CMAKE_COMMAND} -E copy ${webcore_LIBRARIES} ${webcore_DLL} ${ultralightcore_DLL} ${ultralight_DLL} ${appcore_DLL} "${MCC_RUNTIME_OUTPUT_DIRECTORY}/halomods"
	COMMENT "Copying Ultralight DLLs"
	COMMAND_EXPAND_LISTS)

set_target_properties(copy_ultralight_dlls PROPERTIES
	FOLDER "Build Steps")

set(webcore_LIBRARIES ${webcore_LIBRARIES} PARENT_SCOPE)
set(webcore_DLL ${webcore_DLL} PARENT_SCOPE)
set(ultralightcore_DLL ${ultralightcore_DLL} PARENT_SCOPE)
set(ultralight_DLL ${ultralight_DLL} PARENT_SCOPE)
set(appcore_DLL ${appcore_DLL} PARENT_SCOPE)
