project(main)

set(link_libs 	${link_libs} 
				texapp
				model
				objld
				FreeImage)
link_libraries(${link_libs})

set(source 
	./main.cpp 
	./mainapp.cpp
	./callbacks.cpp
	)
add_executable(main ${source})
set_target_properties(main PROPERTIES FOLDER "main")
msvc_build(TARGET main DIR ${headers_dir} LIB ${link_libs})