#version 330 core
layout (std140) uniform Camera {
	uniform mat4 projection;
	uniform mat4 view;
};

layout (location = 0) in vec3 aPos;

void main() {
    gl_Position = projection * view * vec4(aPos, 1.0);
}