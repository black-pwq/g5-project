#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "camapp.h"

CamApp::CamApp(const Options &options) : Application(options)
{
	glfwSetWindowUserPointer(_window, this);
	// setup cursor
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	auto centerX = 0.5f * _windowWidth;
	auto centerY = 0.5f * _windowHeight;
	_input.mouse.position[0] = centerX;
	_input.mouse.position[1] = centerY;
	glfwSetCursorPos(_window, centerX, centerY);

	// init cameras
	movCam.reset(new MovableCamera(
		glm::radians(movCam->defaulfFovyDegree),
		1.0f * _windowWidth / _windowHeight,
		0.1f, 10000.0f));
	orbCam.reset(new OrbitCamera(
		glm::radians(movCam->defaulfFovyDegree),
		1.0f * _windowWidth / _windowHeight,
		0.1f, 10000.0f));
}

CamApp::~CamApp() {}

void CamApp::handleInput()
{
	// camera movement
	glm::vec3 _cameraMoveDirs[6] = {movCam->getView(), -movCam->getRight(), -movCam->getView(), movCam->getRight(), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)};
	for (int i = 0; i < sizeof(_interests) / sizeof(int); i++)
	{
		auto key = _interests[i];
		if (_input.keyboard.keyStates[key] != GLFW_RELEASE)
		{
			// std::cout << glm::to_string(_cameraMoveDirs[i]) << std::endl;
			activeCamera()->move(_cameraMoveDirs[i], movCam->_cameraMoveSpeed * _deltaTime);
		}
	}
}

void CamApp::cursorPosCallback(GLFWwindow *window, double x, double y)
{
	float curr[2] = {static_cast<float>(x), static_cast<float>(y)};
	auto prev = _input.mouse.position;
	if (glfwGetInputMode(_window, GLFW_CURSOR) != GLFW_CURSOR_NORMAL)
	{
		// in observer mode
		float offset[2];
		glm::vec3 mouseRotateAxis[2] = {glm::vec3(0.0f, 1.0f, 0.0f), movCam->getRight()};
		for (int i = 0; i < 2; i++)
		{
			offset[i] = static_cast<float>((curr[i] - prev[i]) * _deltaTime);
			if (offset[i] != 0)
			{
				float radian = static_cast<float>(-offset[i] * _mouseMoveSen);
				movCam->rotate(mouseRotateAxis[i], radian);
			}
		}
	}
	else if (_input.mouse.press.left)
	{
		// pan
		glm::vec3 disp = glm::vec3(0.0f);
		glm::vec3 dirs[] = {-orbCam->getRight(), glm::vec3{.0f, 1.0f, .0f}};
		int windowSize[] = {_windowWidth, _windowHeight};
		for (int i = 0; i < 2; i++)
		{
			auto offset = static_cast<float>((curr[i] - prev[i]) / windowSize[i]);
			disp += offset * dirs[i];
		}
		orbCam->move(disp);
	}
	else if (_input.mouse.press.middle)
	{
		orbCam->rotateAzimuth(-static_cast<float>(glm::radians(curr[0] - prev[0]) * _mouseScrollSen));
		orbCam->rotatePolar(static_cast<float>(glm::radians(curr[1] - prev[1]) * _mouseScrollSen));
	}
	prev[0] = x;
	prev[1] = y;
}

void CamApp::scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
	activeCamera()->zoom(static_cast<float>(activeCamera()->_mouseScrollSen * yoffset));
}

void CamApp::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	Application::keyCallback(window, key, scancode, action, mods);
	switch (action)
	{
	case GLFW_PRESS:
		switch (key)
		{
		case GLFW_KEY_TAB:
		{
			int cursorMod = glfwGetInputMode(_window, GLFW_CURSOR);
			if (cursorMod == GLFW_CURSOR_NORMAL)
				glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			else
			{
				glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
			break;
		}
		case GLFW_KEY_Z:
			activeCamera()->zoomToFit();
			break;
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(_window, true);
			return;

		default:
			break;
		}
		break;

	default:
		break;
	}
}

MovableCamera *CamApp::activeCamera()
{
	int cursorMod = glfwGetInputMode(_window, GLFW_CURSOR);
	if (cursorMod == GLFW_CURSOR_NORMAL)
		return orbCam.get();
	else
		return movCam.get();
}
