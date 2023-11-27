#version 410 core

in vec3 texcoords;
in vec3 viewpos;

out vec4 FragColor;

uniform sampler2DArray tex;

void main() {
    FragColor = texture(tex, texcoords);

    float frac = smoothstep(100, 124, length(viewpos));
    FragColor = mix(FragColor, vec4(0.509, 0.674, 1, 1), frac);
}
