#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "mainapp.h"
#include "../filesys/filesystem.h"

MainApp::MainApp(const Options &options) : TexApp(options)
{
	// set callbacks
	glfwSetCursorPosCallback(_window, ::cursorPosCallback);
	glfwSetScrollCallback(_window, ::scrollCallback);
	glfwSetKeyCallback(_window, ::keyCallback);

	// create a vertex array object
}

MainApp::~MainApp() {}

void MainApp::renderFrame()
{
	TexApp::renderFrame();

	displayImGui();
}

void MainApp::handleInput()
{
	CamApp::handleInput();
}

void MainApp::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	CamApp::keyCallback(window, key, scancode, action, mods);
	if(action == GLFW_PRESS) {
		if(key == GLFW_KEY_Q) {
			std::cout << "call screen shot func" << std::endl;
		}
	}

}