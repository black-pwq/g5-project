#pragma once

#include <memory> 
#include "../shading/shadingapp.h"
#include "../model/model.h"
#include "../common/skybox.h"

enum class TexMode {
	Simple, Blend
};

class TexApp : public ShadingApp {
protected:
	std::unique_ptr<Model> _sphere;
	std::unique_ptr<SimpleMaterial> _simpleMaterial;
	std::unique_ptr<BlendMaterial> _blendMaterial;
	std::unique_ptr<SkyBox> _skybox;
	enum TexMode _texMode = TexMode::Simple;

public:
	TexApp(const Options& options);
	~TexApp();

protected:
	virtual void handleInput();
	virtual void renderFrame();
	virtual void insertImGui();
};