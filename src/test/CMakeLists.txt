project(test)

set(headers ${CMAKE_SOURCE_DIR}/src/filesys 
			${CMAKE_SOURCE_DIR}/src/common 
			${CMAKE_SOURCE_DIR}/src/objloader)
link_directories(${CMAKE_SOURCE_DIR}/libs)
include_directories(headers)

set(link_libs glad glfw3)
link_libraries(${link_libs})

add_executable(test test.cpp)
msvc_build(test ${headers} ${link_libs})