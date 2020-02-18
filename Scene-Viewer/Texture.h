#pragma once

#include <glad/glad.h>

class Texture {
private:
	static std::unordered_map<std::string, GLuint> textures;
public:
	static GLuint getTexture(const std::string& filePath);
};

