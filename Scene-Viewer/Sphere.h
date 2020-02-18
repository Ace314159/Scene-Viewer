#pragma once

#include "Mesh.h"

class Sphere : public Mesh {
private:
	static const unsigned int phiRes = 64;
	static const unsigned int thetaRes = 64;
	static const float PI;

	static std::vector<Vertex> genVertices();
	static std::vector<unsigned int> genIndices();
public:
	Sphere();

	void draw(const Shader& shader) override;
};

