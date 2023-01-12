#pragma once

#include <memory> 
#include "application.h"
#include "glsl_program.h"
#include "../model/model.h"
#include "../common/camera.h"

class MainApp : public Application {
private:
	int _interests[6] = {
		GLFW_KEY_W,
		GLFW_KEY_A,
		GLFW_KEY_S,
		GLFW_KEY_D,
		GLFW_KEY_LEFT_SHIFT,
		GLFW_KEY_SPACE,
	};
	float _mouseMoveSen = 0.05f;
	float _cameraMoveSpeed = 10.0f;
	float _mouseScrollSen = 1.0f;
	// float _movementFactors[2] = {10.0f, 0.05f};
	std::unique_ptr<Model> _cube;
	std::unique_ptr<PerspectiveCamera> _camera;
	std::unique_ptr<GLSLProgram> _shader;

public:
	MainApp(const Options& options);
	~MainApp();
	void cursorPosCallback(GLFWwindow *window, double x, double y);
	void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

private:
	virtual void handleInput();
	virtual void renderFrame();
};