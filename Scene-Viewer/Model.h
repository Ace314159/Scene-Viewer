#pragma once

#include "Mesh.h"
#include "Shader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {
private:
	std::vector<Mesh> meshes;
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh* mesh, const aiScene *scene);
public:
	Model(const char* name);
	inline void draw(const Shader& shader) {
		for(unsigned int i = 0; i < meshes.size(); i++) meshes[i].draw(shader);
	};
};
