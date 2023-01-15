#pragma once

#include <memory> 
#include "application.h"
#include "glsl_program.h"
#include "../model/model.h"
#include "cameras.h"
#include "util.h"

enum class CamMode {
	Still, Move, Orbit
};

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
	float _mouseMoveSen = 0.02f;
	float _cameraMoveSpeed = 10.0f;
	float _mouseScrollSen = .25f;
	std::unique_ptr<MovableCamera> movCam;
	std::unique_ptr<OrbitCamera> orbCam;
	CamMode _camMode = CamMode::Move;

public:
	CamApp(const Options& options);
	~CamApp();
	virtual void cursorPosCallback(GLFWwindow *window, double x, double y);
	virtual void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);
	virtual void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	MovableCamera *activeCamera();

protected:
	virtual void handleInput();
};