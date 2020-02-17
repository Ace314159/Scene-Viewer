#pragma once

#include <glad/glad.h>

class Shader {
private:
	GLuint ID;
public:
	Shader(const char* name);

	inline void use() const { glUseProgram(ID); };
};

