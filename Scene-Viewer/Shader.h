#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
private:
	GLuint ID;
public:
	Shader(const std::string& name);

	inline void use() const { glUseProgram(ID); };

	// Uniforms
	inline void setFloat(const char* name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name), value);
	}
	inline void setInt(const char* name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name), value);
	}
	inline void setVec3(const char* name, const glm::vec3& value) const {
		glUniform3fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(value));
	}
};

