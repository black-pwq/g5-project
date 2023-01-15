cmake_minimum_required(VERSION 3.10)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(g5_project)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")
configure_file(config/root_dir.h.in config/root_dir.h)
configure_file(config/cmake_vs.sh.in ${CMAKE_SOURCE_DIR}/config/cmake_vs.sh @ONLY)

set(headers_dir ${CMAKE_SOURCE_DIR}/includes ${CMAKE_BINARY_DIR}/config)
include_directories(${headers_dir})
set(libs_dir 	${CMAKE_SOURCE_DIR}/libs)
link_directories(${libs_dir})

set(link_libs 	glfw3
				glad)

function(msvc_build)
	set(option OPTIONAL)
	set(single TARGET)
	set(multi DIR LIB)
	cmake_parse_arguments(MSVC_BUILD "${option}" "${single}" "${multi}" ${ARGN})
	if(NOT ( MSVC_BUILD_DIR AND MSVC_BUILD_LIB AND MSVC_BUILD_TARGET))
		message(FATAL_ERROR "usage: msvs_build(TARGET target DIR headers_dir LIB link_libs)")
	endif()
	
	if(MSVC)
		set_target_properties(${MSVC_BUILD_TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
		target_link_options(${MSVC_BUILD_TARGET} PUBLIC /ignore:4099)
	else()
		message("Please use Microsoft Visual Studio")
	endif(MSVC)
	target_include_directories(${MSVC_BUILD_TARGET} PUBLIC ${MSVC_BUILD_DIR})
	target_link_libraries(${MSVC_BUILD_TARGET} ${MSVC_BUILD_LIB})
endfunction(msvc_build )

add_subdirectory(./src)