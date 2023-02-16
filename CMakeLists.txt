cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
include(ExternalProject)
include(FetchContent)

project(delta)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 17)

function(set_common_props TARGET_PROJ)
	get_target_property(TARGET_PROJ_SOURCE_DIR ${TARGET_PROJ} SOURCE_DIR)
	target_include_directories(${TARGET_PROJ} PRIVATE
		${TARGET_PROJ_SOURCE_DIR}
		${PROJECT_SOURCE_DIR})
	get_target_property(TARGET_PROJ_SOURCES ${TARGET_PROJ} SOURCES)
	source_group(TREE ${TARGET_PROJ_SOURCE_DIR} FILES ${TARGET_PROJ_SOURCES})
endfunction()

if(NOT DEFINED MCC_DIR)
	set(MCC_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
else()
	set(MCC_RUNTIME_OUTPUT_DIRECTORY "$<0:>${MCC_DIR}")
endif()

add_subdirectory(thirdparty)
add_subdirectory(common)
add_subdirectory(games)

add_subdirectory(delta)
add_subdirectory(mcc)
