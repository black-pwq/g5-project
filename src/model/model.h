#pragma once

#include "../common/vertex.h"
#include "../objloader/objloader.h"
#include <glad/glad.h>


class Model {
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