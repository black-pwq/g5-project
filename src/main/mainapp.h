#pragma once

#include <memory> 
#include "../shading/shadingapp.h"
#include "../model/model.h"
#include "callbacks.h"

class MainApp : public ShadingApp {
private:
	std::unique_ptr<Model> _cube;
	std::unique_ptr<SimpleMaterial> _simpleMaterial;

public:
	MainApp(const Options& options);
	~MainApp();

private:
	virtual void handleInput();
	virtual void renderFrame();
};