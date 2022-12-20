#include <iostream>
#include "triapp.h"

HelloTriangle::HelloTriangle(const Options& options): Application(options) {
	// create a vertex array object
	glGenVertexArrays(1, &_vao);
	// create a vertex buffer object
	glGenBuffers(1, &_vbo);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

	// specify layout, size of a vertex, data type, normalize, sizeof vertex array, offset of the attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	// create shader
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

	_shader.reset(new GLSLProgram);
	_shader->attachVertexShader(vsCode);
	_shader->attachFragmentShader(fsCode);
	_shader->link();
}

HelloTriangle::~HelloTriangle() {
	if (_vbo != 0) {
		glDeleteBuffers(1, &_vbo);
		_vbo = 0;
	}

	if (_vao != 0) {
		glDeleteVertexArrays(1, &_vao);
		_vao = 0;
	}
}

void HelloTriangle::handleInput() {
	if (_input.keyboard.keyStates[GLFW_KEY_ESCAPE] != GLFW_RELEASE) {
		glfwSetWindowShouldClose(_window, true);
		return ;
	}
}

void HelloTriangle::renderFrame() {
	showFpsInWindowTitle();

	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);

	_shader->use();
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

RenderFlag::RenderFlag(const Options& options): Application(options) {
	// create star shader
	const char* vsCode =
		"#version 330 core\n"
		"layout(location = 0) in vec2 aPosition;\n"
		"void main() {\n"
		"	gl_Position = vec4(aPosition, 0.0f, 1.0f);\n"
		"}\n";

	const char* fsCode =
		"#version 330 core\n"
		"out vec4 fragColor;\n"
		"void main() {\n"
		"	fragColor = vec4(1.0f, 0.870f, 0.0f, 1.0f);\n"
		"}\n";

	_starShader.reset(new GLSLProgram);
	_starShader->attachVertexShader(vsCode);
	_starShader->attachFragmentShader(fsCode);
	_starShader->link();

}

void RenderFlag::handleInput() {
	if (_input.keyboard.keyStates[GLFW_KEY_ESCAPE] != GLFW_RELEASE) {
		glfwSetWindowShouldClose(_window, true);
		return ;
	}
}


void RenderFlag::renderFrame() {
	showFpsInWindowTitle();

	// we use background as the flag
	glClearColor(0.87f, 0.161f, 0.063f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	_starShader->use();
	// for (int i = 0; i < 5; ++i) {
	// 	if (_stars[i] != nullptr) {
	// 		_stars[i]->draw();
	// 	}
	// }
}