#pragma once

class Light
{
public:
	float intensity = 1.0f;
	glm::vec3 color = {1.0f, 1.0f, 1.0f};
};

class AmbientLight : public Light
{
};

class DirectionalLight : public Light
{
public:
	float azimuth = 0;
	float polar = 0;
	glm::vec3 direction()
	{
		return (glm::angleAxis(glm::radians(azimuth), glm::vec3{.0f, 1.0f, .0f}) *
				glm::angleAxis(glm::radians(polar), glm::vec3{-1.0f, .0f, .0f})) *
			   (glm::vec3{.0f, .0f, .0f} - glm::vec3{.0f, .0f, 1.0f});
	}
};

class PointLight : public Light
{
public:
	float kc = 1.0f;
	float kl = 0.0f;
	float kq = 1.0f;
};

class SpotLight : public Light
{
public:
	glm::vec3 position{.0f, .0f, 1.0f};
	glm::vec3 direction{.0f, 0.f, -1.0f};
	float angle = glm::radians(60.0f);
	float kc = 1.0f;
	float kl = 0.0f;
	float kq = 1.0f;
};