
#version 330 core
in vec3 fNormal;
in vec2 fTexCoord;
out vec4 color;  
// material data structure declaration
struct Material {
	vec3 ka;
	vec3 kd;
	vec3 ks;
	float ns;
};
struct BlendMaterial {
	vec3 kds[2];
	float blend;
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
uniform BlendMaterial blendMaterial;
uniform AmbientLight ambientLight;
uniform DirectionalLight directionalLight;
uniform SpotLight spotLight;
uniform sampler2D mapKd;
uniform sampler2D mapKds[2];
uniform bool simple;

vec3 calcDirectionalLight(DirectionalLight directionalLight, vec3 normal, vec3 kd, vec3 ks, float ns);
vec3 calcSpotLight(SpotLight spotLight, vec3 normal, vec3 kd, vec3 ks, float ns);
vec3 calcAmbientReflect(AmbientLight ambientLight, vec3 ka);

void main() {
    vec3 normal = normalize(fNormal);
	vec3 ambient = calcAmbientReflect(ambientLight, material.ka);
	if(simple) {
		vec3 dir = calcDirectionalLight(directionalLight, normal, material.kd, material.ks, material.ns);
		vec3 spec = calcSpotLight(spotLight, normal, material.kd, material.ks, material.ns);
		vec4 comb = vec4(dir + spec + ambient, 1.0f);
		color = texture(mapKd, fTexCoord) * comb;
	} else {
		vec3 b0 = calcDirectionalLight(directionalLight, normal, blendMaterial.kds[0], material.ks, material.ns);
		b0 += calcSpotLight(spotLight, normal, blendMaterial.kds[0], material.ks, material.ns);
		vec3 b1 = calcDirectionalLight(directionalLight, normal, blendMaterial.kds[1], material.ks, material.ns);
		b1 += calcSpotLight(spotLight, normal, blendMaterial.kds[1], material.ks, material.ns);
		color = texture(mapKds[0], fTexCoord) * vec4(b0 + ambient, 1.0f) * (1 - blendMaterial.blend) 
	+ blendMaterial.blend * texture(mapKds[1], fTexCoord) * vec4(b1 + ambient, 1.0f);
	}
}