#pragma once

#include <memory>
#include <vector>

#include "application.h"
#include "glsl_program.h"
#include "camera.h"
#include "root_dir.h"

// #include "cube.h"
// #include "objloader.h"
class SceneRoaming : public Application {
public:
	SceneRoaming(const Options& options);
	
	~SceneRoaming() = default;

	void handleInput() override;

	void renderFrame() override;

private:
	std::vector<std::unique_ptr<Camera>> _cameras;

	int activeCameraIndex = 0;

	// std::unique_ptr<Cube> _cubes[1];

	std::unique_ptr<GLSLProgram> _shader;

	void initShader();
};