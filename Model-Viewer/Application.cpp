#include "stdafx.h"
#include "Window.h"

int main() {
	Window window;

	while(window.isOpen()) {
		window.swapBuffers();
		glfwPollEvents();
	}

	return 0;
}