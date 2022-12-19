#pragma once

#include <memory> 
#include "application.h"
#include "glsl_program.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
};

class HelloTriangle : public Application {
public:
	HelloTriangle(const Options& options);

	~HelloTriangle();

private:
	GLuint _vao = 0;

	GLuint _vbo = 0;

	Vertex _vertices[3] = {
		{ glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
		{ glm::vec3(0.5f, -0.5f, 0.0f),  glm::vec3(0.0f, 1.0f, 0.0f) },
		{ glm::vec3(0.0f,  0.5f, 0.0f),  glm::vec3(0.0f, 0.0f, 1.0f) }
	};

	std::unique_ptr<GLSLProgram> _shader;

	virtual void handleInput();

	virtual void renderFrame();
};