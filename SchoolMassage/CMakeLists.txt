
cmake_minimum_required (VERSION 3.6)
project(SchoolMassage)

#--------------------------------------------------------------------
# Set sources
#--------------------------------------------------------------------


set(SCHOOLMASSAGE_SOURCES 

# Core
src/Main.cpp
src/Application.cpp
src/Application.hpp
src/glad/glad.c
src/stb/stb_image.h
src/GameManager.hpp
src/GameManager.cpp

# Graphics
src/Graphics/Window.hpp
src/Graphics/Window.cpp
src/Graphics/GameRenderer.hpp
src/Graphics/GameRenderer.cpp

# Common
src/Common/DataStructures.hpp
src/Common/Utils.hpp
src/Common/Utils.cpp
src/Common/Common.hpp
src/Common/Common.cpp
src/Common/InputMapping.hpp
src/Common/InputEngine.hpp
src/Common/InputEngine.cpp

# linavg
src/linavg/Backends/GL/GLBackend.cpp
src/linavg/Core/Backend.cpp
src/linavg/Core/Common.cpp
src/linavg/Core/Drawer.cpp
src/linavg/Core/Math.cpp
src/linavg/Core/Renderer.cpp
src/linavg/Core/Text.cpp
src/linavg/Utility/Utility.cpp

# Word
src/World/Object.hpp
src/World/Scene.hpp
src/World/Scene.cpp
src/World/MainScene.hpp
src/World/MainScene.cpp
src/World/Player.hpp
src/World/Player.cpp
src/World/Camera.hpp
src/World/Camera.cpp
src/World/Tilemap.hpp
src/World/Tilemap.cpp

)

#--------------------------------------------------------------------
# Create executable project
#--------------------------------------------------------------------
add_executable(${PROJECT_NAME} ${SCHOOLMASSAGE_SOURCES} )
add_executable(Lina::SchoolMassage ALIAS ${PROJECT_NAME}) 
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

if(NOT WIN32)
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-Wno-pragma-once-outside-header")
endif()

#--------------------------------------------------------------------
# Set include directories
#--------------------------------------------------------------------
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendor/glad/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendor/glm/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendor/glfw/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/vendor/linavg/include)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/vendor/glad/include)
include_directories(${CMAKE_SOURCE_DIR}/vendor/glfw/include)
include_directories(${CMAKE_SOURCE_DIR}/vendor/glm/include)
include_directories(${CMAKE_SOURCE_DIR}/vendor/linavg/include)

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