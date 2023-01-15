
#version 330 core
out vec4 color;
// material data structure declaration
struct Material {
	vec3 ka;
};
// ambient light data structure declaration
struct AmbientLight {
	vec3 color;
	float intensity;
};
// uniform variables
uniform Material material;
uniform AmbientLight ambientLight;
void main() {
	vec3 ambient = material.ka * ambientLight.color * ambientLight.intensity;
	color = vec4(ambient, 1.0f);
}