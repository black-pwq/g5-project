#include <iostream>

int main() {
	const char* vsCode =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec3 aColor;\n"
		"out vec3 color;\n"
		"void main() {\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
		"	color = aColor;\n"
		"}\n";

	const char* fsCode =
		"#version 330 core\n"
		"in vec3 color;\n"
		"out vec4 outColor;\n"
		"void main() {\n"
		"	outColor = vec4(color, 1.0f);\n"
		"}\n";

	std::cout << vsCode << std::endl;
	std::cout << fsCode << std::endl;
	return 0;
}