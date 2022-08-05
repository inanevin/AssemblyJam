
cmake_minimum_required (VERSION 3.6)
project (SchoolMassage)

#--------------------------------------------------------------------
# Download dependencies
#--------------------------------------------------------------------
		
if(WIN32)
	set(PLATFORM "Win64")
endif()
		
if(UNIX)
	set(PLATFORM "Unix")
endif()

#--------------------------------------------------------------------
# Options & Definitions
#--------------------------------------------------------------------
#set(CMAKE_C_COMPILER /c/MinGW/bin/gcc.exe)
#set(CMAKE_CXX_COMPILER /c/MinGW/bin/g++.exe)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_SUPPRESS_REGENERATION true)

set(TARGET_ARCHITECTURE "x64")


if(WIN32)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
endif()

#--------------------------------------------------------------------
# Set source & header dirs
#--------------------------------------------------------------------


#--------------------------------------------------------------------
# Sub directories
#--------------------------------------------------------------------

## add_subdirectory(LinaVG)
add_subdirectory(Game)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Game)

