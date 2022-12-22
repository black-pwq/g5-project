#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"

class FullscreenQuad {
public:
	FullscreenQuad();

	FullscreenQuad(const FullscreenQuad&) = delete;

	FullscreenQuad(FullscreenQuad&& rhs) noexcept;

	~FullscreenQuad();

	void draw() const;
private:
	GLuint _vao;
	GLuint _vbo;
};