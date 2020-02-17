#include "stdafx.h"
#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Model.h"

int main() {
	try {
		Window window;
		Mesh::initVAO();
		Shader shader("solidColor");
		Model model("nanosuit/nanosuit.obj");

		while(window.isOpen()) {
			model.draw(shader);
			window.swapBuffers();
			glfwPollEvents();
		}
	} catch(const std::exception & e) {
		std::cout << e.what() << std::endl;
		throw e;
	}

	

	return 0;
}