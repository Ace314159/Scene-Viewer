#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Shader.h"

struct Vertex {
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct TextureData {
	GLuint ID;
	std::string type;
};

class Mesh {
private:
	GLuint VBO, EBO;
public:
	static GLuint VAO;
	static void initVAO();

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<TextureData> textures;

	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices,
		std::vector<TextureData> textures);
	void draw(const Shader& shader);
};

