add_library(glad ${CMAKE_SOURCE_DIR}/src/libs/glad.c)
set_target_properties(glad PROPERTIES FOLDER "lib")

ADD_SUBDIR()