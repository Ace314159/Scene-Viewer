#include "stdafx.h"
#include "Shader.h"

Shader::Shader(const std::string& name) {
	std::ifstream vFile;
	std::ifstream fFile;
	vFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	vFile.open("assets/shaders/" + name + ".vert");
	fFile.open("assets/shaders/" + name + ".frag");
	std::stringstream vStream, fStream;
	vStream << vFile.rdbuf();
	fStream << fFile.rdbuf();
	vFile.close();
	fFile.close();
	
	std::string vCode = vStream.str();
	std::string fCode = fStream.str();
	const char* vCodeC = vCode.c_str();
	const char* fCodeC = fCode.c_str();
	
	int success;
	char infoLog[512];

	GLuint vID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vID, 1, &vCodeC, nullptr);
	glCompileShader(vID);
	glGetShaderiv(vID, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(vID, 512, nullptr, infoLog);
		throw std::runtime_error("Vertex Shader " + name + " failed to compile: " + infoLog);
	}

	GLuint fID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fID, 1, &fCodeC, nullptr);
	glCompileShader(fID);
	glGetShaderiv(fID, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(fID, 512, nullptr, infoLog);
		throw std::runtime_error("Fragment Shader " + name + " failed to compile: " + infoLog);
	}

	ID = glCreateProgram();
	glAttachShader(ID, vID);
	glAttachShader(ID, fID);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(ID, 512, nullptr, infoLog);
		throw std::runtime_error("Shader " + name + " failed to link: " + infoLog);
	}

	glDeleteShader(vID);
	glDeleteShader(fID);
}
