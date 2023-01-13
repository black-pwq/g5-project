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


	// create a vertex array object
	_camera.reset(new OperatableCamera(
		glm::radians(_camera->defaulfFovyDegree),
		1.0f * _windowWidth / _windowHeight,
		0.1f, 10000.0f));
}

CamApp::~CamApp() {}

void CamApp::handleInput()
{
	// camera movement
	glm::vec3 _cameraMoveDirs[6] = {_camera->transform.getFront(), -_camera->transform.getRight(), -_camera->transform.getFront(), _camera->transform.getRight(), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)};
	for (int i = 0; i < sizeof(_interests) / sizeof(int); i++)
	{
		auto key = _interests[i];
		if (_input.keyboard.keyStates[key] != GLFW_RELEASE)
		{
			_camera->move(_cameraMoveDirs[i], _camera->_cameraMoveSpeed * _deltaTime);
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
		glm::quat rotation = _camera->transform.rotation;
		glm::vec3 mouseRotateAxis[2] = {glm::vec3(0.0f, 1.0f, 0.0f), _camera->transform.getRight()};
		for (int i = 0; i < 2; i++)
		{
			offset[i] = static_cast<float>((curr[i] - prev[i]) * _deltaTime);
			if (offset[i] != 0)
			{
				float radian = static_cast<float>(-offset[i] * _mouseMoveSen);
				_camera->rotate(mouseRotateAxis[i], radian);
			}
		}
	}
	else if (_input.mouse.press.left)
	{
		// pan
		glm::vec3 disp = glm::vec3(0.0f);
		glm::vec3 dirs[] = {-_camera->getRight(), _camera->getUp()};
		int windowSize[] = {_windowWidth, _windowHeight};
		for (int i = 0; i < 2; i++)
		{
			auto offset = static_cast<float>((curr[i] - prev[i]) / windowSize[i]);
			disp += offset * dirs[i];
		}
		_camera->pan(disp);
	}
	else if(_input.mouse.press.middle) {
		// orbit
		glm::vec3 center = {0.0f, 0.0f, 0.0f};
		float degree = static_cast<float>(curr[0] - prev[0]);
		_camera->orbit(center, degree);
	}
	prev[0] = x;
	prev[1] = y;
}

void CamApp::scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
	_camera->zoom(static_cast<float>(_camera->_mouseScrollSen * yoffset));
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
				{
					glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
					_camera->toObserver();
				}
			else
				glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			break;
		}
		case GLFW_KEY_Z:
			_camera->zoomToFit();
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