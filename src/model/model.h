#pragma once

#include "../common/vertex.h"
#include "../objloader/objloader.h"
#include <glad/glad.h>
#include "../common/transform.h"

class Model {
	public:
	Transform transform;

	protected:
	Objloader _obj;
	GLuint _vao;
	GLuint _vbo;
	GLuint _ebo;

	public:
	Model( std::string &filepath);
	virtual void draw();

	protected:
	void bindToGLBuffers();
};