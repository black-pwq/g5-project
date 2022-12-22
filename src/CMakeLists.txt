include_directories(./common)
add_subdirectory(./common)

add_subdirectory(./test)
set_target_properties(test PROPERTIES FOLDER "test")
add_subdirectory(./test/app)
set_target_properties(testapp PROPERTIES FOLDER "test")

add_subdirectory(./objloader) 
set_target_properties(objloader PROPERTIES FOLDER "objloader") 