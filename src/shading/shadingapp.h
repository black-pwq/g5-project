#pragma once

#include <memory> 
#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_impl_glfw.h"
#include "../libs/imgui/imgui_impl_opengl3.h"
#include "../camapp/camapp.h"
// #include "../model/model.h"
// #include "../main/callbacks.h"
#include "material.h"
#include "lights.h"

enum class RenderMode {
	Ambient, Lambert, Phong
};

class ShadingApp : public CamApp {
private:
	// std::unique_ptr<Model> _cube;
	// std::unique_ptr<GLSLProgram> _shader;

	// materials
	std::unique_ptr<AmbientMaterial> _ambientMaterial;
	std::unique_ptr<LambertMaterial> _lambertMaterial;
	std::unique_ptr<PhongMaterial> _phongMaterial;

	// shaders
	std::unique_ptr<GLSLProgram> _ambientShader;
	std::unique_ptr<GLSLProgram> _lambertShader;
	std::unique_ptr<GLSLProgram> _phongShader;

	// lights
	std::unique_ptr<AmbientLight> _ambientLight;
	std::unique_ptr<DirectionalLight> _directionalLight;
	std::unique_ptr<SpotLight> _spotLight;

	RenderMode _renderMode = RenderMode::Phong;

public:
	ShadingApp(const Options& options);
	~ShadingApp();
	GLSLProgram *activeShader();

protected:
	virtual void handleInput();
	virtual void renderFrame();
	virtual void insertImGui();
	virtual void displayImGui(int flags =
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings);
	void initLights();
	void initMaterial();
	// I = ka * albedo
	void initAmbientShader();
	// I = ka * albedo + kd * max(cos<I, n>, 0)
	void initLambertShader();
	// I = ka * albedo + kd * cos<I, n> + ks * (max(cos<R, V>, 0) ^ ns)
	void initPhongShader();
};