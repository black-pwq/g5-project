#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "mainapp.h"
#include "../filesys/filesystem.h"

MainApp::MainApp(const Options &options) : CamApp(options)
{	
	// set callbacks
	glfwSetCursorPosCallback(_window, ::cursorPosCallback);
	glfwSetScrollCallback(_window, ::scrollCallback);
	glfwSetKeyCallback(_window, ::keyCallback);

	// create a vertex array object
	_cube.reset(new Model(getAssetFullPath("obj/cube.obj")));

	// create shader
	_shader.reset(new GLSLProgram);
	_shader->attachVertexShaderFromFile(getAssetFullPath("shader/test/tri.vs"));
	_shader->attachFragmentShaderFromFile(getAssetFullPath("shader/test/tri.fs"));
	_shader->link();
}

MainApp::~MainApp() {}

void MainApp::renderFrame()
{
	showFpsInWindowTitle();

	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	_shader->use();
	// auto localMat = _cube->transform.getLocalMatrix();
	_shader->setUniformMat4("model", _cube->transform.getLocalMatrix());
	_shader->setUniformMat4("view", activeCamera()->getViewMatrix());
	_shader->setUniformMat4("projection", activeCamera()->getProjectionMatrix());
	_cube->draw();
}

void MainApp::handleInput()
{
	CamApp::handleInput();
}