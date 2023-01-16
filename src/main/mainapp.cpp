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

void MainApp::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	CamApp::keyCallback(window, key, scancode, action, mods);
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_Q)
		{
			std::cout << "call screen shot func" << std::endl;
			// Make the BYTE array, factor of 3 because it's RBG.
			BYTE *pixels = new BYTE[3 * _windowWidth * _windowHeight];

			glReadPixels(0, 0, _windowWidth, _windowHeight, GL_BGR, GL_UNSIGNED_BYTE, pixels);

			// Convert to FreeImage format & save to file
			FIBITMAP *image = FreeImage_ConvertFromRawBits(pixels, _windowWidth, _windowHeight, 3 * _windowWidth, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);
			std::cout << FreeImage_Save(FIF_BMP, image, "./test.bmp", 0) << std::endl;

			// Free resources
			FreeImage_Unload(image);
			delete[] pixels;
		}
	}
}