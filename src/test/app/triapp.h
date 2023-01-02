#pragma once

#include <memory> 
#include "application.h"
#include "glsl_program.h"
#include "../../model/model.h"

class HelloTriangle : public Application {
public:
	HelloTriangle(const Options& options);

	~HelloTriangle();

private:
	std::unique_ptr<Model> _cube;

	std::unique_ptr<GLSLProgram> _shader;

	virtual void handleInput();

	virtual void renderFrame();
};