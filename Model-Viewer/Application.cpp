#include "stdafx.h"
#include "Shader.h"
#include "Window.h"

int main() {
	Window window;
	
	try {
		Shader shader("solidColor");
	} catch(const std::exception& e) {
		std::cout << e.what() << std::endl;
		return -1;
	}

	while(window.isOpen()) {
		window.swapBuffers();
		glfwPollEvents();
	}


	return 0;
}