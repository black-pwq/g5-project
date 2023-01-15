#pragma once
#include <glm/glm.hpp>
#include "../common/texture2d.h"

class AmbientMaterial {
	public:
	glm::vec3 ka = {0.03f, 0.03f, 0.03f};
};

// I = sum { kd * Light[i] * cos(theta[i]) }
class LambertMaterial {
	public:
	glm::vec3 kd = {1.0f, 1.0f, 1.0f};
};

// I = ka * Ia + sum { (kd * cos(theta[i]) + ks * cos(theta[i])^ns ) * Light[i] }
class PhongMaterial {
	public:
	glm::vec3 ka{0.03f, 0.03f, 0.03f};
	glm::vec3 kd{1.0f, 1.0f, 1.0f};
	glm::vec3 ks{1.0f, 1.0f, 1.0f};
	float ns = 10.0f;
};

struct SimpleMaterial {
	std::shared_ptr<Texture2D> mapKd;
};