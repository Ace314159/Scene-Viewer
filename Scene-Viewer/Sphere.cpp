#include "stdafx.h"
#include "Sphere.h"

Sphere::Sphere() : Mesh(genVertices(), genIndices(), {}) {}

const float Sphere::PI = 3.14159265359f;

std::vector<Vertex> Sphere::genVertices() {
	std::vector<Vertex> vertices;

	for(unsigned int phiN = 0; phiN <= phiRes; phiN++) {
		for(unsigned int thetaN = 0; thetaN <= thetaRes; thetaN++) {
			float phiP = (float)phiN / phiRes;
			float phi = phiP * PI;
			float thetaP = (float)thetaN / thetaRes;
			float theta = thetaP * 2 * PI;
			glm::vec3 pos = {std::sin(phi) * std::cos(theta), std::cos(phi), std::sin(phi)* std::sin(theta)};
			vertices.push_back({
				pos,
				pos,
				{pos.x, pos.y},
			});
		}
	}

	return vertices;
}

std::vector<unsigned int> Sphere::genIndices() {
	std::vector<unsigned int> indices;

	bool oddRow = false;
	for(int phiN = 0; phiN < phiRes; phiN++) {
		if(oddRow) {
			for(int thetaN = thetaRes; thetaN >= 0; thetaN--) {
				indices.push_back((phiN + 1) * (thetaRes + 1) + thetaN);
				indices.push_back((phiN + 0) * (thetaRes + 1) + thetaN);
			}
		} else {
			for(int thetaN = 0; thetaN <= thetaRes; thetaN++) {
				indices.push_back((phiN + 0) * (thetaRes + 1) + thetaN);
				indices.push_back((phiN + 1) * (thetaRes + 1) + thetaN);
			}
		}
		oddRow = !oddRow;
	}

	return indices;
}

void Sphere::draw(const Shader& shader) {
	shader.use();

	glBindVertexArray(VAO);
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(Vertex));
	glVertexArrayElementBuffer(VAO, EBO);

	glDrawElements(GL_TRIANGLE_STRIP, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
}
