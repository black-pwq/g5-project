project(testapp)

set(link_libs 	${link_libs} 
				app
				model)
link_libraries(${link_libs})

set(source 
	./triapp.cpp 
	./runtri.cpp)
add_executable(testapp ${source})
set_target_properties(testapp PROPERTIES FOLDER "test")
msvc_build(TARGET testapp DIR ${headers_dir} LIB ${link_libs})