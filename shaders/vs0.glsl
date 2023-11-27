#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 uv;

uniform mat4 view;
uniform mat4 model;
uniform mat4 proj;

out vec3 texcoords;
out vec3 viewpos;

void main() {
    gl_Position = proj * view * model * vec4(position, 1.0);
    texcoords = uv;

    viewpos = (view * model * vec4(position, 1.0)).xyz;
}
