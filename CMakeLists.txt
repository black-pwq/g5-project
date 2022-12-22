cmake_minimum_required(VERSION 3.10)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(g5_project)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

include_directories(${CMAKE_SOURCE_DIR}/includes)
link_directories(${CMAKE_SOURCE_DIR}/libs)

add_library(glad ${CMAKE_SOURCE_DIR}/src/libs/glad.c)
set_target_properties(glad PROPERTIES FOLDER "lib")

add_subdirectory(./src/test)
set_target_properties(test PROPERTIES FOLDER "test")
add_subdirectory(./src/test/app)
set_target_properties(testapp PROPERTIES FOLDER "test")

add_subdirectory(./src/objloader) 
set_target_properties(objloader PROPERTIES FOLDER "xmttest") 

