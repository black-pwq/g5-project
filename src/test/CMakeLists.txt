cmake_minimum_required(VERSION 3.10)

project(test)

set(link_libs glad glfw3)
link_libraries(${link_libs})

include_directories(${CMAKE_SOURCE_DIR}/src/filesys)
add_executable(test test.cpp)

if(MSVC)
	set_target_properties(test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
	target_link_options(test PUBLIC /ignore:4099)
else()
	message("Please use Microsoft Visual Studio")
endif(MSVC)

target_include_directories(test PUBLIC ${CMAKE_SOURCE_DIR}/includes)
target_link_libraries(test ${link_libs})
