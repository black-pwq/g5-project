cmake_minimum_required(VERSION 3.10)

project(xmttest)

set(link_libs glad glfw3)
link_libraries(${link_libs})

add_executable(xmttest xmttest.cpp)

if(MSVC)
	set_target_properties(xmttest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
	target_link_options(xmttest PUBLIC /ignore:4099)
else()
	message("Please use Microsoft Visual Studio")
endif(MSVC)

target_include_directories(xmttest PUBLIC ${CMAKE_SOURCE_DIR}/includes)
target_link_libraries(xmttest ${link_libs})
