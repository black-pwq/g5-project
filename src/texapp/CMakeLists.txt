set(link_libs 	${link_libs} 
				shaapp
				model
				objld
				tex2d)
link_libraries(${link_libs})

set(source 
	./texapp.cpp)
add_library(texapp ${source})
set_target_properties(texapp PROPERTIES FOLDER "main")
# msvc_build(TARGET texapp DIR ${headers_dir} LIB ${link_libs})