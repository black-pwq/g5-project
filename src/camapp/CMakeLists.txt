project(camapp)

set(link_lib ${link_lib} app)
link_libraries(${link_lib})

set(source ./camapp.cpp 
			./cameras.cpp 
			./util.cpp)
add_library(camapp ${source})

set_target_properties(camapp PROPERTIES FOLDER "main")