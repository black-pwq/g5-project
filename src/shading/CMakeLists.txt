project(shaapp)

set(link_libs 	${link_libs} 
				camapp
				imgui)
link_libraries(${link_libs})

set(source 
	./shadingapp.cpp )
add_library(shaapp ${source})
set_target_properties(shaapp PROPERTIES FOLDER "main")
# msvc_build(TARGET shaapp DIR ${headers_dir} LIB ${link_libs})