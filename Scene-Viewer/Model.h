#pragma once

#include "Mesh.h"
#include "Shader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {
private:
	std::string dir;
	std::vector<Mesh> meshes;
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh* mesh, const aiScene *scene);
	std::vector<TextureData> loadMaterialTexture(aiMaterial* mat, aiTextureType type,
		const std::string& typeName);
public:
	Model(const std::string& fileName);
	inline void draw(const Shader& shader) {
		for(unsigned int i = 0; i < meshes.size(); i++) meshes[i].draw(shader);
	};
};
