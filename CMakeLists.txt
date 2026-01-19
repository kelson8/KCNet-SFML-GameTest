cmake_minimum_required(VERSION 3.28)

project(CMakeSFMLProject LANGUAGES CXX)
set(PROJECT_NAME "CMakeSFMLProject")

file(GLOB SOURCES "src/*.cpp" "src/util/*.cpp" "src/menus/debug/*.cpp")
file(GLOB HEADERS "src/*.h" "src/util/*.h" "src/menus/debug/*.h")

# set(SOURCES
	# src/main.cpp 
	# src/game.cpp
	# src/window_manager.cpp
	# src/player.cpp
	# src/menus/debug/imgui_menu.cpp
	
# )

# set(HEADERS
	# src/game.h
	# src/window_manager.h
	# src/player.h
	# src/menus/debug/imgui_menu.h
# )

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

add_executable(main
	${SOURCES}
	${HEADERS}
	)
# target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE 
	# SFML::Graphics
	ImGui-SFML::ImGui-SFML
	fmt::fmt
	)
	
# include_directories(src)
	
# This probably isn't required, I forgot to re-add the ImGui SFML library
target_include_directories(main PRIVATE
	src/
	${imgui-sfml_SOURCE_DIR}/include)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)