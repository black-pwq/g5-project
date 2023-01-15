
#version 330 core
in vec3 fNormal;
out vec4 color;  
// material data structure declaration
struct Material {
	vec3 ka;
	vec3 kd;
	vec3 ks;
	float ns;
};
struct AmbientLight {
	vec3 color;
	float intensity;
};
struct DirectionalLight {
	vec3 direction;
	float intensity;
	vec3 color;
};
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

vec3 calcDirectionalLight(DirectionalLight directionalLight, vec3 normal, vec3 kd, vec3 ks, float ns);
vec3 calcSpotLight(SpotLight spotLight, vec3 normal, vec3 kd, vec3 ks, float ns);
vec3 calcAmbientReflect(AmbientLight ambientLight, vec3 ka);
void main() {
    vec3 normal = normalize(fNormal);
	vec3 ambient = calcAmbientReflect(ambientLight, material.ka);
	vec3 comb = calcDirectionalLight(directionalLight, normal, material.kd, material.ks, material.ns) + 
				calcSpotLight(spotLight, normal, material.kd, material.ks, material.ns) + 
				ambient;

    color = vec4(comb, 1.0f);
}