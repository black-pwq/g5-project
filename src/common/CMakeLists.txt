add_library(app ./application.cpp
				./glsl_program.cpp)	
set_target_properties(app PROPERTIES FOLDER "common")

link_libraries(${link_libs} stb)
add_library(tex2d ./texture.cpp
					./texture2d.cpp)		
set_target_properties(tex2d PROPERTIES FOLDER "common")