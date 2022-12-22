cmake_minimum_required(VERSION 3.10)

project(objloader)

set(link_libs glad glfw3)
link_libraries(${link_libs})

include_directories(${CMAKE_SOURCE_DIR}/src/common)
include_directories(${CMAKE_SOURCE_DIR}/src/objloader)
set(source 
	# ${CMAKE_SOURCE_DIR}/src/common/application.cpp 
	# ${CMAKE_SOURCE_DIR}/src/common/glsl_program.cpp 
	# ${CMAKE_SOURCE_DIR}/src/common/transform.cpp 
	# ${CMAKE_SOURCE_DIR}/src/common/camera.cpp 
	
	# ./cube.cpp
	# ./objloader.cpp
	# ./triapp.cpp 
	./runtri.cpp)
# set(source 
# 	./objloader.cpp
# 	./triapp.cpp)
add_executable(objloader ${source})

if(MSVC)
	set_target_properties(objloader PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
	target_link_options(objloader PUBLIC /ignore:4099)
else()
	message("Please use Microsoft Visual Studio")
endif(MSVC)

target_include_directories(objloader PUBLIC ${CMAKE_SOURCE_DIR}/includes)
target_link_libraries(objloader ${link_libs})
