#version 410 core

in vec2 texcoords;
out vec4 FragColor;

uniform sampler2D tex;

void main() {
    FragColor = texture(tex, texcoords);
}
