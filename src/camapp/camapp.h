#pragma once

#include <memory> 
#include "application.h"
#include "glsl_program.h"
#include "../model/model.h"
#include "../common/camera.h"
#include "cameras.h"
#include "util.h"

class CamApp : public Application {
protected:
	int _interests[6] = {
		GLFW_KEY_W,
		GLFW_KEY_A,
		GLFW_KEY_S,
		GLFW_KEY_D,
		GLFW_KEY_LEFT_SHIFT,
		GLFW_KEY_SPACE,
	};
	// float _movementFactors[2] = {10.0f, 0.05f};
	float _mouseMoveSen = 0.02f;
	float _cameraMoveSpeed = 10.0f;
	float _mouseScrollSen = 1.0f;
	std::unique_ptr<OperatableCamera> _camera;

public:
	CamApp(const Options& options);
	~CamApp();
	void cursorPosCallback(GLFWwindow *window, double x, double y);
	void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

protected:
	virtual void handleInput();
	// virtual void renderFrame();
};