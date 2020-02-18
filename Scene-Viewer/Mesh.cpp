#include "stdafx.h"
#include "Mesh.h"

GLuint Mesh::VAO = -1;

void Mesh::initVAO() {
	glCreateVertexArrays(1, &VAO);

	glEnableVertexArrayAttrib(VAO, 0);
	glEnableVertexArrayAttrib(VAO, 1);
	glEnableVertexArrayAttrib(VAO, 2);

	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, Vertex::pos));
	glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, Vertex::normal));
	glVertexArrayAttribFormat(VAO, 2, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, Vertex::texCoords));

	glVertexArrayAttribBinding(VAO, 0, 0);
	glVertexArrayAttribBinding(VAO, 1, 0);
	glVertexArrayAttribBinding(VAO, 2, 0);
}

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, GLuint textureID) {
	this->vertices = vertices;
	this->indices = indices;
	this->textureID = textureID;

	glCreateBuffers(1, &VBO);
	glCreateBuffers(1, &EBO);

	glNamedBufferData(EBO, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	glNamedBufferData(VBO, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void Mesh::draw(const Shader& shader) {
	shader.use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	shader.setInt("tex", 0);

	glBindVertexArray(VAO);
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(Vertex));
	glVertexArrayElementBuffer(VAO, EBO);

	glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
}