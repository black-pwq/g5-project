#version 330 core
layout(location = 0) in vec3 aPos;  
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec3 aTexCoord;
out vec3 color;
void main() {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
        color = vec3(.5f, .5f, .5f);
}