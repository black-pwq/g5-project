cmake_minimum_required(VERSION 3.10)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(g5_project)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")
configure_file(config/root_dir.h.in config/root_dir.h)
configure_file(config/cmake_vs.sh.in ${CMAKE_SOURCE_DIR}/config/cmake_vs.sh @ONLY)

add_library(glad ${CMAKE_SOURCE_DIR}/src/libs/glad.c)
set_target_properties(glad PROPERTIES FOLDER "lib")

set(headers_dir ${CMAKE_SOURCE_DIR}/includes ${CMAKE_BINARY_DIR}/config)
include_directories(${headers_dir})
set(libs_dir 	${CMAKE_SOURCE_DIR}/libs)
link_directories(${libs_dir})

set(link_libs 	glfw3
				glad)

function(msvc_build target_name headers_dir libs_dir)
	if(MSVC)
		set_target_properties(${target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
		target_link_options(${target_name} PUBLIC /ignore:4099)
	else()
		message("Please use Microsoft Visual Studio")
	endif(MSVC)
	target_include_directories(${target_name} PUBLIC ${headers_dir})
	target_link_libraries(${target_name} ${libs_dir})
endfunction(msvc_build target_name headers_dir libs_dir)

add_subdirectory(./src)
# add_subdirectory(./src/filesys)