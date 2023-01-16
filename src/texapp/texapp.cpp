#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "texapp.h"

TexApp::TexApp(const Options &options) : ShadingApp(options)
{
	// create a vertex array object
	_sphere.reset(new Model(getAssetFullPath("obj/sphere.obj")));

	std::shared_ptr<Texture2D> cubeTex =
		std::make_shared<ImageTexture2D>(getAssetFullPath("texture/miscellaneous/earthmap.jpg"));
	std::shared_ptr<Texture2D> faceTex =
		std::make_shared<ImageTexture2D>(getAssetFullPath("texture/miscellaneous/planet_Quom1200.png"));
	_simpleMaterial.reset(new SimpleMaterial);
	_simpleMaterial->mapKd = cubeTex;

	_blendMaterial.reset(new BlendMaterial);
	_blendMaterial->kds[0] = glm::vec3(1.0f, 1.0f, 1.0f);
	_blendMaterial->kds[1] = glm::vec3(1.0f, 1.0f, 1.0f);
	_blendMaterial->mapKds[0] = cubeTex;
	_blendMaterial->mapKds[1] = faceTex;
	_blendMaterial->blend = 0.0f;

	const std::vector<std::string> skyboxTextureRelPaths = {
		"texture/skybox/Right_Tex.jpg",
		"texture/skybox/Left_Tex.jpg",
		"texture/skybox/Down_Tex.jpg",
		"texture/skybox/Up_Tex.jpg",
		"texture/skybox/Front_Tex.jpg",
		"texture/skybox/Back_Tex.jpg"};
	std::vector<std::string> skyboxTextureFullPaths;
	for (size_t i = 0; i < skyboxTextureRelPaths.size(); ++i)
	{
		skyboxTextureFullPaths.push_back(getAssetFullPath(skyboxTextureRelPaths[i]));
	}
	_skybox.reset(new SkyBox(skyboxTextureFullPaths));
}

TexApp::~TexApp() {}

void TexApp::renderFrame()
{
	ShadingApp::renderFrame();

	activeShader()->setUniformMat4("model", _sphere->transform.getLocalMatrix());
	switch (_texMode)
	{
	case TexMode::Simple:
		activeShader()->setUniformBool("simple", true);
		_simpleMaterial->mapKd->bind();
		break;
	case TexMode::Blend:
		activeShader()->setUniformBool("simple", false);
		activeShader()->setUniformVec3("blendMaterial.kds[0]", _blendMaterial->kds[0]);
		activeShader()->setUniformVec3("blendMaterial.kds[1]", _blendMaterial->kds[1]);
		activeShader()->setUniformFloat("blendMaterial.blend", _blendMaterial->blend);
		// 4.3 TODO: enable textures and transform textures to gpu
		//----------------------------------------------------------------
		GLint v[2];
		for (GLint i = 0; i < 2; i++)
		{
			v[i] = i;
			_blendMaterial->mapKds[i]->bind(i);
		}
		glUniform1iv(glGetUniformLocation(activeShader()->_handle, "mapKds"), 2, v);
		//----------------------------------------------------------------
		break;

	default:
		break;
	}
	_sphere->draw();
	_skybox->draw(activeCamera()->getProjectionMatrix(), activeCamera()->getViewMatrix());

	displayImGui();
}

void TexApp::handleInput()
{
	CamApp::handleInput();
}

void TexApp::insertImGui()
{
	ShadingApp::insertImGui();

	const auto flags =
		ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings;
	bool show_windows = true;
	if (!ImGui::Begin("Texture", &show_windows, flags))
	{
		ImGui::End();
	}
	else
	{
		ImGui::Text("Render Mode");
		ImGui::Separator();
		ImGui::RadioButton("Simple Texture Shading", (int *)&_texMode, (int)(TexMode::Simple));
		ImGui::NewLine();

		ImGui::RadioButton("Blend Texture Shading", (int *)&_texMode, (int)(TexMode::Blend));
		ImGui::ColorEdit3("kd1", (float *)&_blendMaterial->kds[0]);
		ImGui::ColorEdit3("kd2", (float *)&_blendMaterial->kds[1]);
		ImGui::SliderFloat("blend", &_blendMaterial->blend, 0.0f, 1.0f);
		ImGui::NewLine();

		ImGui::End();
	}
}