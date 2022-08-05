#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Author: Inan Evin
# www.inanevin.com
# 
# Copyright (C) 2018 Inan Evin
# 
# Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, 
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions 
# and limitations under the License.
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.6)
project(Game)

#--------------------------------------------------------------------
# Set sources
#--------------------------------------------------------------------
set (GAME_SOURCES
	# CORE
	src/Main.cpp
)

#--------------------------------------------------------------------
# Set headers
#--------------------------------------------------------------------
set(GAME_HEADERS

)

#--------------------------------------------------------------------
# Define the library & create an alias
#--------------------------------------------------------------------
add_executable(${PROJECT_NAME} ${GAME_SOURCES} ${GAME_HEADERS})
add_executable(Lina::Sandbox ALIAS ${PROJECT_NAME}) 

#--------------------------------------------------------------------
# Set include directories
#--------------------------------------------------------------------

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)

#--------------------------------------------------------------------
# Subdirectories & linking
#--------------------------------------------------------------------


# Link libraries (e.g. logging)
#target_link_libraries(${PROJECT_NAME} 
	# ${CMAKE_THREAD_LIBS_INIT}     # Needed for unix builds to link to pthread

#)

#--------------------------------------------------------------------
# Packages
#--------------------------------------------------------------------
find_package(OpenGL REQUIRED)

# Launch Lina Header tool prior to building to prepare the reflection data for runtime.

## add_custom_command(
## TARGET ${PROJECT_NAME}
## PRE_BUILD
## COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR}/LinaHeaderTool/bin/ LinaHeader.exe)

#--------------------------------------------------------------------
# Folder structuring in visual studio
#--------------------------------------------------------------------
if(MSVC_IDE)
	foreach(source IN LISTS GAME_HEADERS GAME_SOURCES)
		get_filename_component(source_path "${source}" PATH)
		string(REPLACE "${LinaEngine_SOURCE_DIR}" "" relative_source_path "${source_path}")
		string(REPLACE "/" "\\" source_path_msvc "${relative_source_path}")
				source_group("${source_path_msvc}" FILES "${source}")
	endforeach()
endif()


