
cmake_minimum_required (VERSION 3.6)
project(SchoolMassage)

#--------------------------------------------------------------------
# Set sources
#--------------------------------------------------------------------


set(SCHOOLMASSAGE_SOURCES 

src/Main.cpp
)

set(SCHOOLMASSAGE_HEADERS

)

#--------------------------------------------------------------------
# Create executable project
#--------------------------------------------------------------------
add_executable(${PROJECT_NAME} ${SCHOOLMASSAGE_SOURCES} ${SCHOOLMASSAGE_HEADERS} )
add_executable(Lina::SchoolMassage ALIAS ${PROJECT_NAME}) 

#--------------------------------------------------------------------
# Set include directories
#--------------------------------------------------------------------
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

#--------------------------------------------------------------------
# Links
#--------------------------------------------------------------------
## target_link_libraries(${PROJECT_NAME} 
## PRIVATE Engine
## )

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