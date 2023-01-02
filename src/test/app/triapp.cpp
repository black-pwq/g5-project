#include <iostream>
#include "triapp.h"
#include "../../filesys/filesystem.h"

HelloTriangle::HelloTriangle(const Options& options): Application(options) {
	// create a vertex array object
	_cube.reset(new Model(getAssetFullPath("obj/cube.obj")));

	// create shader
	_shader.reset(new GLSLProgram);
	_shader->attachVertexShaderFromFile(getAssetFullPath("shader/test/tri.vs"));
	_shader->attachFragmentShaderFromFile(getAssetFullPath("shader/test/tri.fs"));
	_shader->link();
}

HelloTriangle::~HelloTriangle() {}

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
	_cube->draw();
}