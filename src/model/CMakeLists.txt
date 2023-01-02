project(model)

include_directories(../filesys)
add_library(model ./model.cpp)
set_target_properties(model PROPERTIES FOLDER "lib")