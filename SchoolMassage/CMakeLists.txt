
cmake_minimum_required (VERSION 3.6)
project(SchoolMassage)

#--------------------------------------------------------------------
# Set sources
#--------------------------------------------------------------------


set(SCHOOLMASSAGE_SOURCES 

src/Main.cpp
src/glad/glad.c
src/stb/stb_image.h
src/Graphics/Window.hpp
src/Graphics/Window.cpp
src/Common/DataStructures.hpp

)

#--------------------------------------------------------------------
# Create executable project
#--------------------------------------------------------------------
add_executable(${PROJECT_NAME} ${SCHOOLMASSAGE_SOURCES} )
add_executable(Lina::SchoolMassage ALIAS ${PROJECT_NAME}) 
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

#--------------------------------------------------------------------
# Set include directories
#--------------------------------------------------------------------
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendor/glad/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendor/glm/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendor/glfw/include)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/vendor/glad/include)
include_directories(${CMAKE_SOURCE_DIR}/vendor/glfw/include)
include_directories(${CMAKE_SOURCE_DIR}/vendor/glm/include)

#--------------------------------------------------------------------
# Links
#--------------------------------------------------------------------
if(WIN32)
 target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendor/glfw/lib/glfw3.lib)
else()
 find_package(OpenGL REQUIRED)
 target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendor/glfw/lib/libglfw3.a OpenGL::GL 
  "-framework Cocoa"
  "-framework IOKit")
endif()


if(WIN32)

# Copy engine resources to project solution directory to run within IDE.
add_custom_command(
TARGET ${PROJECT_NAME}
POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/_Resources" "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/")

# Copy engine resources to binary directory
add_custom_command(
TARGET ${PROJECT_NAME}
POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/_Resources" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/")

else()

endif()
#--------------------------------------------------------------------
# Folder structuring in visual studio
#--------------------------------------------------------------------
if(MSVC_IDE)
	foreach(source IN LISTS SCHOOLMASSAGE_HEADERS SCHOOLMASSAGE_SOURCES)
		get_filename_component(source_path "${source}" PATH)
		string(REPLACE "${SCHOOLMASSAGE_SOURCE_DIR}" "" relative_source_path "${source_path}")
		string(REPLACE "/" "\\" source_path_msvc "${relative_source_path}")
				source_group("${source_path_msvc}" FILES "${source}")
	endforeach()
endif()