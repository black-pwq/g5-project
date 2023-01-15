#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "mainapp.h"
#include "../filesys/filesystem.h"

MainApp::MainApp(const Options &options) : ShadingApp(options)
{	
	// set callbacks
	glfwSetCursorPosCallback(_window, ::cursorPosCallback);
	glfwSetScrollCallback(_window, ::scrollCallback);
	glfwSetKeyCallback(_window, ::keyCallback);

	// create a vertex array object
	_cube.reset(new Model(getAssetFullPath("obj/cube.obj")));

}

MainApp::~MainApp() {}

void MainApp::renderFrame()
{
	ShadingApp::renderFrame();

	activeShader()->setUniformMat4("model", _cube->transform.getLocalMatrix());
	_cube->draw();

	displayImGui();
}

void MainApp::handleInput()
{
	CamApp::handleInput();
}