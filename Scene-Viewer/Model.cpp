#include "stdafx.h"
#include "Model.h"
#include "Texture.h"

Model::Model(const std::string& fileName) {
	std::string name = fileName.substr(0, fileName.find_last_of('.'));
	dir = "assets/scenes/" + name + "/";

	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(dir + fileName, aiProcess_Triangulate | aiProcess_FlipUVs);

	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		throw std::runtime_error("Model " + name + " failed to load: " + import.GetErrorString());
	}
	
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
	for(unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	for(unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<TextureData> textures;

	for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex = {
			{mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z},
			{mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z},
			{0, 0},
		};
		
		if(mesh->mTextureCoords[0])
			vertex.texCoords = {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
		vertices.push_back(vertex);
	}

	for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		indices.insert(indices.end(), face.mIndices, face.mIndices + face.mNumIndices);
	}

	if(mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<TextureData> diffuseMaps = loadMaterialTexture(material, aiTextureType_DIFFUSE, "diffuse");
		std::vector<TextureData> specularMaps = loadMaterialTexture(material, aiTextureType_SPECULAR,
			"specular");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return {vertices, indices, textures};
}

std::vector<TextureData> Model::loadMaterialTexture(aiMaterial* mat, aiTextureType type,
	const std::string& typeName) {
	std::vector<TextureData> textures;
	for(unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
		aiString path;
		mat->GetTexture(type, i, &path);
		textures.push_back({Texture::getTexture(dir + std::string(path.C_Str())), typeName});
	}
	return textures;
}
