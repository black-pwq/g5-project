
#version 330 core
out vec4 color;  
in vec3 fPosition;
in vec3 fNormal;
// material data structure declaration
struct Material {
	vec3 ka;
	vec3 kd;
	vec3 ks;
	float ns;
};
// ambient light data structure declaration
struct AmbientLight {
	vec3 color;
	float intensity;
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
uniform AmbientLight ambientLight;
uniform DirectionalLight directionalLight;
uniform SpotLight spotLight;
uniform vec3 cameraPos;
vec3 calcDirectionalLight(vec3 normal) {
	vec3 lightDir = normalize(-directionalLight.direction);
	vec3 diffuse = max(dot(lightDir, normal), 0.0f) * material.kd;
    vec3 reflectDir = -lightDir + 2 * dot(normal, lightDir) * normal;
    vec3 viewDir = normalize(cameraPos - fPosition);
	vec3 spec = pow(max(dot(reflectDir, viewDir), 0.0), material.ns) * material.ks;
	return directionalLight.intensity * directionalLight.color * (diffuse + spec);
}
vec3 calcSpotLight(vec3 normal) {
	vec3 lightDir = normalize(spotLight.position - fPosition);
	float theta = acos(-dot(lightDir, normalize(spotLight.direction)));
	if (theta > spotLight.angle) {
		return vec3(0.0f, 0.0f, 0.0f);
	}
	vec3 diffuse = max(dot(lightDir, normal), 0.0f) * material.kd;
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 viewDir = normalize(cameraPos - fPosition);
	vec3 spec = pow(max(dot(reflectDir, viewDir), 0.0), material.ns) * material.ks;
	float distance = length(spotLight.position - fPosition);
	float attenuation = 1.0f / (spotLight.kc + spotLight.kl * distance + spotLight.kq * distance * distance);
	return spotLight.color * spotLight.intensity * attenuation * (diffuse + spec);
}
void main() {
    vec3 normal = normalize(fNormal);
	vec3 ambient = ambientLight.intensity * ambientLight.color * material.ka;
	vec3 comb = calcDirectionalLight(normal) + calcSpotLight(normal) + ambient;

    color = vec4(comb, 1.0f);
}