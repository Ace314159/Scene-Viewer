#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
	Window();
	~Window();

	inline bool isOpen() { return !glfwWindowShouldClose(window); };
	inline void swapBuffers() { glfwSwapBuffers(window); };
	GLFWwindow* window;
};

inline void APIENTRY glDebugCallback(GLenum source, GLenum mType, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam) {
	std::string src;
	switch(source) {
	case GL_DEBUG_SOURCE_API:
		src = "Windows";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		src = "Shader Compiler";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		src = "Third Party";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		src = "Application";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		src = "Other";
		break;
	}

	std::string type;
	switch(mType) {
	case GL_DEBUG_TYPE_ERROR:
		type = "Error";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		type = "Deprecated Behavior";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		type = "Undefined Behavior";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		type = "Portability Error";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		type = "Performance Error";
		break;
	case GL_DEBUG_TYPE_OTHER:
		type = "Other Message";
		break;
	}

	switch(severity) {
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		std::cout << "GL NOTIFICATION - " + src + " " + type + ": " + message << std::endl;
		break;
	case GL_DEBUG_SEVERITY_LOW:
		std::cout << "GL LOW - " + src + " " + type + ": " + message << std::endl;
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		std::cout << "GL MEDIUM - " + src + " " + type + ": " + message << std::endl;
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		throw std::runtime_error("GL HIGH - " + src + " " + type + ": " + message);
		break;
	}
}
