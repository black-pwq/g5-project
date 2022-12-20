cmake_minimum_required(VERSION 3.10)

project(xmttestappx)

set(link_libs glad glfw3)
link_libraries(${link_libs})

include_directories(${CMAKE_SOURCE_DIR}/src/common)
set(source 
	${CMAKE_SOURCE_DIR}/src/common/application.cpp 
	${CMAKE_SOURCE_DIR}/src/common/glsl_program.cpp 
	./triapp.cpp 
	./runtri.cpp)
add_executable(xmttestappx ${source})

if(MSVC)
	set_target_properties(xmttestappx PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
	target_link_options(xmttestappx PUBLIC /ignore:4099)
else()
	message("Please use Microsoft Visual Studio")
endif(MSVC)

target_include_directories(xmttestappx PUBLIC ${CMAKE_SOURCE_DIR}/includes)
target_link_libraries(xmttestappx ${link_libs})
