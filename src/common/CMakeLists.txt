add_library(app ./application.cpp
				./glsl_program.cpp)	

set_target_properties(app PROPERTIES FOLDER "common")