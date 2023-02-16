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
endif()

set_target_properties(mcclauncher PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${MCC_RUNTIME_OUTPUT_DIRECTORY}"
	FOLDER "MCC Projects")

add_custom_command(TARGET mcclauncher POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${webcore_LIBRARIES} $<TARGET_RUNTIME_DLLS:mcclauncher> $<TARGET_FILE_DIR:mcclauncher>
	COMMAND_EXPAND_LISTS)
