project(testapp)

set(link_libs 	${link_libs} 
				app)
link_libraries(${link_libs})

set(source 
	./triapp.cpp 
	./runtri.cpp)
add_executable(testapp ${source})

msvc_build(testapp ${headers} ${link_libs})