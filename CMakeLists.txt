cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
include(ExternalProject)
include(FetchContent)

project(delta)

add_subdirectory(thirdparty)
add_subdirectory(common)
add_subdirectory(games)
add_subdirectory(launcher)
add_subdirectory(interface)
