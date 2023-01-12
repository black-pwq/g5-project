#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "mainapp.h"
#include "callbacks.h"
#include "../filesys/filesystem.h"

MainApp::MainApp(const Options &options) : Application(options)
{
	glfwSetWindowUserPointer(_window, this);
	// setup cursor
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	auto centerX = 0.5f * _windowWidth;
	auto centerY = 0.5f * _windowHeight;
	_input.mouse.position[0] = centerX;
	_input.mouse.position[1] = centerY;
	glfwSetCursorPos(_window, centerX, centerY);
	glfwSetCursorPosCallback(_window, ::cursorPosCallback);
	glfwSetScrollCallback(_window, ::scrollCallback);

	// create a vertex array object
	_cube.reset(new Model(getAssetFullPath("obj/cube.obj")));

	_camera.reset(new PerspectiveCamera(
		glm::radians(_camera->defaulfFovyDegree),
		1.0f * _windowWidth / _windowHeight,
		0.1f, 10000.0f));

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
	glClear(GL_COLOR_BUFFER_BIT);

	_shader->use();
	// auto localMat = _cube->transform.getLocalMatrix();
	_shader->setUniformMat4("model", _cube->transform.getLocalMatrix());
	_shader->setUniformMat4("view", _camera->getViewMatrix());
	_shader->setUniformMat4("projection", _camera->getProjectionMatrix());
	_cube->draw();
}

void MainApp::handleInput()
{
	if (_input.keyboard.keyStates[GLFW_KEY_ESCAPE] != GLFW_RELEASE)
	{
		glfwSetWindowShouldClose(_window, true);
		return;
	}
	// camera movement
	glm::vec3 _cameraMoveDirs[6] = {_camera->transform.getFront(), -_camera->transform.getRight(), -_camera->transform.getFront(), _camera->transform.getRight(), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)};
	for (int i = 0; i < sizeof(_interests) / sizeof(int); i++)
	{
		auto key = _interests[i];
		if (_input.keyboard.keyStates[key] != GLFW_RELEASE)
		{
			_camera->transform.position += _cameraMoveDirs[i] * _cameraMoveSpeed * _deltaTime;
		}
	}
	// zoom to fit
	if(_input.keyboard.keyStates[GLFW_KEY_Z] == GLFW_PRESS) {
		_camera->fovy = glm::radians(45.0f);
	}
}

void MainApp::cursorPosCallback(GLFWwindow *window, double x, double y)
{
	double curr[2];
	curr[0] = x;
	curr[1] = y;
	auto prev = _input.mouse.position;
	glm::vec3 _mouseRotateAxis[2] = {glm::vec3(0.0f, 1.0f, 0.0f), _camera->transform.getRight()};
	for (int i = 0; i < 2; i++)
	{
		if (curr[i] != prev[i])
		{
			auto diff = curr[i] - prev[i];
			float radian = static_cast<float>(-diff * _deltaTime * _mouseMoveSen / 2);
			glm::quat old = _camera->transform.rotation;
			_camera->transform.rotation = glm::quat{glm::cos(radian), sin(radian) * _mouseRotateAxis[i]} * old;
		}
	}
	prev[0] = x;
	prev[1] = y;
}

void MainApp::scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
	float fovy = static_cast<float>(_mouseScrollSen * (glm::degrees(_camera->fovy) - yoffset));
	if(fovy <= _camera->minFovyDegree) {
		fovy = _camera->minFovyDegree;
	} else if (fovy >= _camera->maxFovyDegree) {
		fovy = _camera->maxFovyDegree;
	}
	_camera->fovy = glm::radians(fovy);
}