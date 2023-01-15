#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "shadingapp.h"

ShadingApp::ShadingApp(const Options &options) : CamApp(options)
{
	// init materials
	initMaterial();
	// init lights
	initLights();

	// init imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init();

	// create shader
	initAmbientShader();
	initLambertShader();
	initPhongShader();
}

ShadingApp::~ShadingApp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ShadingApp::renderFrame()
{
	showFpsInWindowTitle();

	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	switch (_renderMode)
	{
	case RenderMode::Ambient:
		_ambientShader->use();
		// 1. transfer mvp matrix to the shader
		_ambientShader->setUniformMat4("projection", activeCamera()->getProjectionMatrix());
		_ambientShader->setUniformMat4("view", activeCamera()->getViewMatrix());
		// 2. transfer material attributes to the shader
		_ambientShader->setUniformVec3("material.ka", _ambientMaterial->ka);
		// 3. transfer light attributes to the shader
		_ambientShader->setUniformVec3("ambientLight.color", _ambientLight->color);
		_ambientShader->setUniformFloat("ambientLight.intensity", _ambientLight->intensity);
		break;
	case RenderMode::Lambert:
		_lambertShader->use();
		// 1. transfer mvp matrix to the shader
		_lambertShader->setUniformMat4("projection", activeCamera()->getProjectionMatrix());
		_lambertShader->setUniformMat4("view", activeCamera()->getViewMatrix());
		// 2. transfer material attributes to the shader
		_lambertShader->setUniformVec3("material.kd", _lambertMaterial->kd);
		// 3. transfer light attributes to the shader
		_lambertShader->setUniformVec3("spotLight.position", _spotLight->position);
		_lambertShader->setUniformVec3("spotLight.direction", _spotLight->direction);
		_lambertShader->setUniformFloat("spotLight.intensity", _spotLight->intensity);
		_lambertShader->setUniformVec3("spotLight.color", _spotLight->color);
		_lambertShader->setUniformFloat("spotLight.angle", _spotLight->angle);
		_lambertShader->setUniformFloat("spotLight.kc", _spotLight->kc);
		_lambertShader->setUniformFloat("spotLight.kl", _spotLight->kl);
		_lambertShader->setUniformFloat("spotLight.kq", _spotLight->kq);
		_lambertShader->setUniformVec3("directionalLight.direction", _directionalLight->direction());
		_lambertShader->setUniformFloat("directionalLight.intensity", _directionalLight->intensity);
		_lambertShader->setUniformVec3("directionalLight.color", _directionalLight->color);
		break;
	case RenderMode::Phong:
		_phongShader->use();
		// 1. transfer the mvp matrices to the shader
		_phongShader->setUniformMat4("projection", activeCamera()->getProjectionMatrix());
		_phongShader->setUniformMat4("view", activeCamera()->getViewMatrix());

		// 2. TODO: transfer the camera position to the shader
		// ----------------------------------------------------------------
		_phongShader->setUniformVec3("cameraPos", activeCamera()->getEye());
		// ----------------------------------------------------------------

		// 3. TODO: transfer the material attributes to the shader
		// -----------------------------------------------------------
		_phongShader->setUniformVec3("material.ka", _phongMaterial->ka);
		_phongShader->setUniformVec3("material.kd", _phongMaterial->kd);
		_phongShader->setUniformVec3("material.ks", _phongMaterial->ks);
		_phongShader->setUniformFloat("material.ns", _phongMaterial->ns);
		// -----------------------------------------------------------

		// 4. TODO: transfer the light attributes to the shader
		// -----------------------------------------------------------
		_phongShader->setUniformVec3("ambientLight.color", _ambientLight->color);
		_phongShader->setUniformFloat("ambientLight.intensity", _ambientLight->intensity);
		_phongShader->setUniformVec3("spotLight.position", _spotLight->position);
		_phongShader->setUniformVec3("spotLight.direction", _spotLight->direction);
		_phongShader->setUniformFloat("spotLight.intensity", _spotLight->intensity);
		_phongShader->setUniformVec3("spotLight.color", _spotLight->color);
		_phongShader->setUniformFloat("spotLight.angle", _spotLight->angle);
		_phongShader->setUniformFloat("spotLight.kc", _spotLight->kc);
		_phongShader->setUniformFloat("spotLight.kl", _spotLight->kl);
		_phongShader->setUniformFloat("spotLight.kq", _spotLight->kq);
		_phongShader->setUniformVec3("directionalLight.direction", _directionalLight->direction());
		_phongShader->setUniformFloat("directionalLight.intensity", _directionalLight->intensity);
		_phongShader->setUniformVec3("directionalLight.color", _directionalLight->color);
		// -----------------------------------------------------------
		break;
	}

	// activeShader()->setUniformMat4("model", _cube->transform.getLocalMatrix());
	// _cube->draw();
}

void ShadingApp::handleInput()
{
	CamApp::handleInput();
}

void ShadingApp::initLights()
{
	_ambientLight.reset(new AmbientLight);

	_directionalLight.reset(new DirectionalLight);
	_directionalLight->intensity = 0.5f;
	// _directionalLight->rotation = glm::angleAxis(glm::radians(45.0f), glm::normalize(glm::vec3(-1.0f)));

	_spotLight.reset(new SpotLight);
	_spotLight->intensity = 0.5f;
	_spotLight->position = glm::vec3(0.0f, 0.0f, 5.0f);
	// _spotLight->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
}

void ShadingApp::displayImGui()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	const auto flags =
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings;

	if (!ImGui::Begin("Control Panel", nullptr, flags))
	{
		ImGui::End();
	}
	else
	{
		ImGui::Text("Render Mode");
		ImGui::Separator();

		ImGui::RadioButton("ambient", (int *)&_renderMode, (int)(RenderMode::Ambient));
		ImGui::ColorEdit3("ka##1", (float *)&_ambientMaterial->ka);
		ImGui::NewLine();

		ImGui::RadioButton("lambert", (int *)&_renderMode, (int)(RenderMode::Lambert));
		ImGui::ColorEdit3("kd##2", (float *)&_lambertMaterial->kd);
		ImGui::NewLine();

		ImGui::RadioButton("phong", (int *)&_renderMode, (int)(RenderMode::Phong));
		ImGui::ColorEdit3("ka##3", (float *)&_phongMaterial->ka);
		ImGui::ColorEdit3("kd##3", (float *)&_phongMaterial->kd);
		ImGui::ColorEdit3("ks##3", (float *)&_phongMaterial->ks);
		ImGui::SliderFloat("ns##3", &_phongMaterial->ns, 1.0f, 50.0f);
		ImGui::NewLine();

		ImGui::Text("ambient light");
		ImGui::Separator();
		ImGui::SliderFloat("intensity##1", &_ambientLight->intensity, 0.0f, 1.0f);
		ImGui::ColorEdit3("color##1", (float *)&_ambientLight->color);
		ImGui::NewLine();

		ImGui::Text("directional light");
		ImGui::Separator();
		ImGui::SliderFloat("intensity##2", &_directionalLight->intensity, 0.0f, 1.0f);
		ImGui::ColorEdit3("color##2", (float *)&_directionalLight->color);
		ImGui::SliderFloat("azimuth##3", (float *)&_directionalLight->azimuth, .0f, 360.0f);
		ImGui::SliderFloat("polar##3", (float *)&_directionalLight->polar, .0f, 360.0f);
		ImGui::NewLine();

		ImGui::Text("spot light");
		ImGui::Separator();
		ImGui::SliderFloat("intensity##3", &_spotLight->intensity, 0.0f, 1.0f);
		ImGui::ColorEdit3("color##3", (float *)&_spotLight->color);
		ImGui::SliderFloat("angle##3", (float *)&_spotLight->angle, 0.0f, glm::radians(180.0f), "%f rad");
		ImGui::SliderFloat("pos.x##3", (float *)&_spotLight->position.x, -100.0f, 100.0f);
		ImGui::SliderFloat("pos.y##3", (float *)&_spotLight->position.y, -100.0f, 100.0f);
		ImGui::SliderFloat("pos.z##3", (float *)&_spotLight->position.z, -100.0f, 100.0f);
		ImGui::NewLine();

		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ShadingApp::initAmbientShader()
{
	_ambientShader.reset(new GLSLProgram);
	_ambientShader->attachVertexShaderFromFile(getAssetFullPath("shader/ambient.vs"));
	_ambientShader->attachFragmentShaderFromFile(getAssetFullPath("shader/ambient.fs"));
	_ambientShader->link();
}
void ShadingApp::initLambertShader()
{
	_lambertShader.reset(new GLSLProgram);
	_lambertShader->attachVertexShaderFromFile(getAssetFullPath("shader/lambert.vs"));
	_lambertShader->attachFragmentShaderFromFile(getAssetFullPath("shader/lambert.fs"));
	_lambertShader->link();
}
void ShadingApp::initPhongShader()
{
	_phongShader.reset(new GLSLProgram);
	_phongShader->attachVertexShaderFromFile(getAssetFullPath("shader/phong.vs"));
	_phongShader->attachFragmentShaderFromFile(getAssetFullPath("shader/phong.fs"));
	_phongShader->link();
}

void ShadingApp::initMaterial()
{
	_ambientMaterial.reset(new AmbientMaterial());
	_lambertMaterial.reset(new LambertMaterial());
	_phongMaterial.reset(new PhongMaterial());
}

GLSLProgram *ShadingApp::activeShader()
{
	switch (_renderMode)
	{
	case RenderMode::Ambient:
		return _ambientShader.get();
	case RenderMode::Lambert:
		return _lambertShader.get();
	case RenderMode::Phong:
		return _phongShader.get();

	default:
		break;
	}
	return nullptr;
}