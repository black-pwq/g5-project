#pragma once
#include <memory> 
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "application.h"
#include "glsl_program.h"
#include "transform.h"
#include "vertex.h"
class Cube {
public:
	Cube(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

	~Cube();
	Cube(const Cube& rhs) = delete;

	Cube(Cube&& rhs) noexcept;
	
	void draw();

	Transform transform;
	std::vector<Vertex> _vertices;
	std::vector<uint32_t> _indices;
private:
	// vertices of the table represented in model's own coordinate

	
	// opengl objects
	GLuint _vao = 0;
	GLuint _vbo = 0;
	GLuint _ebo = 0;
};
