#pragma once

#include <memory> 
#include "../camapp/camapp.h"
#include "../model/model.h"
#include "callbacks.h"

class MainApp : public CamApp {
private:
	std::unique_ptr<Model> _cube;
	std::unique_ptr<GLSLProgram> _shader;

public:
	MainApp(const Options& options);
	~MainApp();

private:
	virtual void handleInput();
	virtual void renderFrame();
};