project(test)

set(headers_dir ${headers_dir}
			${CMAKE_SOURCE_DIR}/src/filesys 
			${CMAKE_SOURCE_DIR}/src/common )
include_directories(${headers_dir})

set(link_libs ${link_libs} objld)
link_libraries(${link_libs})

add_executable(test test.cpp)
set_target_properties(test PROPERTIES FOLDER "test")
msvc_build(TARGET test DIR ${headers_dir} LIB ${link_libs})

add_subdirectory(./app)