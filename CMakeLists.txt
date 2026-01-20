cmake_minimum_required(VERSION 3.28)

set(PROJECT_NAME "KCNet-SFML-GameTest")
project(${PROJECT_NAME} LANGUAGES CXX)

file(GLOB SOURCES 
	"src/*.cpp" 
	"src/util/*.cpp" 
	"src/menus/*.cpp"
	"src/menus/debug/*.cpp")

file(GLOB HEADERS 
	"src/*.h" 
	"src/util/*.h" 
	"src/menus/*.h"
	"src/menus/debug/*.h")

# New for Visual Studio filters
# TODO Make this neater later.
file(GLOB SOURCES_MAIN "src/*.cpp")
file(GLOB SOURCES_UTIL "src/util/*.cpp")
file(GLOB SOURCES_MENU "src/menus/*.cpp")
file(GLOB SOURCES_MENU_IMGUI "src/menus/debug/*.cpp")

file(GLOB HEADERS_MAIN "src/*.h")
file(GLOB HEADERS_UTIL "src/util/*.h")
file(GLOB HEADERS_MENU "src/menus/*.h")
file(GLOB HEADERS_MENU_IMGUI "src/menus/debug/*.h")
#

# 
# https://github.com/eliasdaler/imgui-sfml-fetchcontent/blob/master/dependencies/CMakeLists.txt

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Switched to C++20
# set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

#---------
# SFML
#---------
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

#---------
# ImGui and other dependencies
#---------
add_subdirectory(dependencies)

#---------
# Main program
#---------

add_executable(${PROJECT_NAME}
	${SOURCES}
	${HEADERS}
	)

# Setup precompiled headers
# Disabled for now.
# target_precompile_headers(${PROJECT_NAME} PRIVATE src/pch.h)

# Setup the libraries to link with.
target_link_libraries(${PROJECT_NAME} PRIVATE 
	SFML::Graphics
	SFML::Audio
	SFML::System
	ImGui-SFML::ImGui-SFML
	fmt::fmt
	)
	
# Include directories for the project, I prefer to use util/ or menus/ for other folders.
# So just the src and ImGui include directories are in here
target_include_directories(${PROJECT_NAME} PRIVATE
	src/
	${imgui-sfml_SOURCE_DIR}/include)

# Set the Visual Studio startup project to be main.
#set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

#------
# Copy files to build
#------

# Copy the fonts to the build folder
# https://discourse.cmake.org/t/copying-files-with-destination-folder-depending-on-build-config/10686
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/fonts/"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/fonts")

# Copy the resources, such as music to the build folder.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/resources/"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources")

# New for Visual Studio filters
# https://stackoverflow.com/questions/33808087/cmake-how-to-create-visual-studio-filters
source_group("src"            	FILES ${SOURCES_MAIN})
source_group("src/util"         FILES ${SOURCES_UTIL})
source_group("src/menus"        FILES ${SOURCES_MENU})
source_group("src/menus/debug"  FILES ${SOURCES_MENU_IMGUI})

source_group("src"        		FILES ${HEADERS_MAIN})
source_group("src/util"        	FILES ${HEADERS_UTIL})
source_group("src/menus"        FILES ${HEADERS_MENU})
source_group("src/menus/debug"	FILES ${HEADERS_MENU_IMGUI})