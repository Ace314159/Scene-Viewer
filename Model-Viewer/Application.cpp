#include "stdafx.h"
#include "Mesh.h"
#include "Shader.h"
#include "Window.h"

int main() {
	Window window;
	Mesh::initVAO();
	Shader shader("solidColor");

	while(window.isOpen()) {
		shader.use();
		window.swapBuffers();
		glfwPollEvents();
	}

	return 0;
}