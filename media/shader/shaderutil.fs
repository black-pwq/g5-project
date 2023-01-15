#version 330 core
in vec3 fPosition;
in vec3 fNormal;
uniform vec3 cameraPos;
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

vec3 calcDiffuseReflect(vec3 lightDir, vec3 normal, vec3 kd) { // light direction should be normalized
	return max(dot(lightDir, normal), 0.0f) * kd;
}
vec3 calcSpecularReflect(vec3 lightDir, vec3 normal, vec3 ks, float ns) { // given eye position and frag pos.
    vec3 reflectDir = -lightDir + 2 * dot(normal, lightDir) * normal;
    vec3 viewDir = normalize(cameraPos - fPosition);
	vec3 spec = pow(max(dot(reflectDir, viewDir), 0.0), ns) * ks;
	return spec;
}

vec3 calcDirectionalReflect(vec3 lightDir, vec3 normal, vec3 kd, vec3 ks, float ns) {
	vec3 diffuse = calcDiffuseReflect(lightDir, normal, kd);
	vec3 spec = calcSpecularReflect(lightDir, normal, ks, ns);
	return diffuse + spec;
}
vec3 calcDirectionalLight(DirectionalLight directionalLight, vec3 normal, vec3 kd, vec3 ks, float ns) {
	vec3 lightDir = normalize(-directionalLight.direction);
	vec3 reflectColor = calcDirectionalReflect(lightDir, normal, kd, ks, ns);
	return directionalLight.intensity * directionalLight.color * reflectColor;
}

vec3 calcSpotReflect(SpotLight spotLight, vec3 normal, vec3 kd, vec3 ks, float ns) {
	vec3 lightDir = normalize(spotLight.position - fPosition);
	float theta = acos(-dot(lightDir, normalize(spotLight.direction)));
	if (theta > spotLight.angle) {
		return vec3(0.0f, 0.0f, 0.0f);
	}
	vec3 diffuse = calcDiffuseReflect(lightDir, normal, kd);
	vec3 spec = calcSpecularReflect(lightDir, normal, ks, ns);
	return spec + diffuse;
}
vec3 calcSpotLight(SpotLight spotLight, vec3 normal, vec3 kd, vec3 ks, float ns) {
	vec3 reflectColor = calcSpotReflect(spotLight, normal, kd, ks, ns);
	float distance = length(spotLight.position - fPosition);
	float attenuation = 1.0f / (spotLight.kc + spotLight.kl * distance + spotLight.kq * distance * distance);
	return spotLight.color * spotLight.intensity * attenuation * reflectColor;
}

vec3 calcAmbientReflect(AmbientLight ambientLight, vec3 ka) {
	return ambientLight.intensity * ambientLight.color * ka;
}