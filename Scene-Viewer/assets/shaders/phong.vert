#version 330 core
layout (std140) uniform Camera {
	uniform mat4 projection;
	uniform mat4 view;
	uniform vec3 cameraPos;
};

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 texCoords;
out vec3 normal;
out vec3 fragPos;

void main() {
	texCoords = aTexCoords;
	normal = aNormal;
	fragPos = aPos;
    gl_Position = projection * view * vec4(aPos, 1.0);
}