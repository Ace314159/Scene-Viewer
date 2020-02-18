#pragma once

#include <glad/glad.h>

class Shader {
private:
	GLuint ID;
public:
	Shader(const std::string& name);

	inline void use() const { glUseProgram(ID); };

	// Uniforms
	inline void setInt(const char* name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name), value);
	}
};

