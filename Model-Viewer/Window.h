#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
private:
	GLFWwindow* window;
public:
	Window();
	~Window();

	inline bool isOpen() { return !glfwWindowShouldClose(window); };
	inline void swapBuffers() { glfwSwapBuffers(window); };
};

