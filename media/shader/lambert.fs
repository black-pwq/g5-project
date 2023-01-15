
#version 330 core
in vec3 fPosition;
in vec3 fNormal;
out vec4 color;
// material data structure declaration
struct Material {
	vec3 kd;
};
// directional light data structure declaration
struct DirectionalLight {
	vec3 direction;
	float intensity;
	vec3 color;
};
// spot light data structure declaration
struct SpotLight {
	vec3 position;
	vec3 direction;
	float intensity;
	vec3 color;
	float angle;
	float kc;
	float kl;
	float kq;
};
// uniform variables
uniform Material material;
uniform DirectionalLight directionalLight;
uniform SpotLight spotLight;
vec3 calcDirectionalLight(vec3 normal) {
	vec3 lightDir = normalize(-directionalLight.direction);
	vec3 diffuse = directionalLight.color * max(dot(lightDir, normal), 0.0f) * material.kd;
	return directionalLight.intensity * diffuse ;
}
vec3 calcSpotLight(vec3 normal) {
	vec3 lightDir = normalize(spotLight.position - fPosition);
	float theta = acos(-dot(lightDir, normalize(spotLight.direction)));
	if (theta > spotLight.angle) {
		return vec3(0.0f, 0.0f, 0.0f);
	}
	vec3 diffuse = spotLight.color * max(dot(lightDir, normal), 0.0f) * material.kd;
	float distance = length(spotLight.position - fPosition);
	float attenuation = 1.0f / (spotLight.kc + spotLight.kl * distance + spotLight.kq * distance * distance);
	return spotLight.intensity * attenuation * diffuse;
}
void main() {
	vec3 normal = normalize(fNormal);
	vec3 diffuse = calcDirectionalLight(normal) + calcSpotLight(normal);
	color = vec4(diffuse, 1.0f);
}