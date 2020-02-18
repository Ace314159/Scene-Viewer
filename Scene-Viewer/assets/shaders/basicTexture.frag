#version 330 core
out vec4 outColor;

in vec2 texCoords;
in vec3 normal;

uniform sampler2D tex;

void main() {
    outColor = texture(tex, texCoords);
} 