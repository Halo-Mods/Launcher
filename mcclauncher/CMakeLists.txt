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

add_dependencies(mcclauncher mcclib)

set_target_properties(mcclauncher PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${MCC_RUNTIME_OUTPUT_DIRECTORY}")

add_custom_command(TARGET mcclauncher POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${webcore_LIBRARIES} $<TARGET_RUNTIME_DLLS:mcclauncher> $<TARGET_FILE_DIR:mcclauncher>
	COMMAND_EXPAND_LISTS)
