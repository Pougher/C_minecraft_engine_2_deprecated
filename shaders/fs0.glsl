#version 410 core

in vec3 texcoords;
out vec4 FragColor;

uniform sampler2DArray tex;

void main() {
    FragColor = texture(tex, texcoords);
}
