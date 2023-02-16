add_executable(mcclauncher WIN32
	ul_interface.cpp
	ul_interface.h
	game_launcher.cpp
	game_launcher.h
	main.cpp
	mcclauncher_private_pch.h)

set_common_props(mcclauncher)

target_precompile_headers(mcclauncher PRIVATE
	mcclauncher_private_pch.h)

target_link_libraries(mcclauncher PRIVATE
	detourslib
	ultralightlibs
	appcore
	common)

if(UE4_INTEGRATION)
	add_dependencies(mcclauncher
		mcclib)
	target_compile_definitions(mcclauncher PRIVATE
		UE4_INTEGRATION)
else()
	add_dependencies(mcclauncher
		interface)
endif()

add_dependencies(mcclauncher
	copy_ultralight_dlls)

target_link_libraries(mcclauncher PRIVATE
	delayimp)

foreach(DLL IN ITEMS ${ultralightcore_DLL} ${ultralight_DLL} ${appcore_DLL})
	cmake_path(GET DLL FILENAME DLL_FILENAME)
	target_link_options(mcclauncher PRIVATE
		"/DELAYLOAD:${DLL_FILENAME}")
endforeach()

set_target_properties(mcclauncher PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${MCC_RUNTIME_OUTPUT_DIRECTORY}"
	FOLDER "MCC Projects")
