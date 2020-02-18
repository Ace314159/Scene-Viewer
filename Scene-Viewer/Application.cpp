#include "stdafx.h"
#include "Camera.h"
#include "Model.h"
#include "Shader.h"
#include "Sphere.h"
#include "Window.h"

int main() {
	try {
		Window window;

		Camera camera(window.window);

		Mesh::initVAO();
		Model model("nanosuit.obj");
		Sphere sphere;
		Shader shader("phong");

		while(window.isOpen()) {
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			camera.update();
			model.draw(shader);
			sphere.draw(shader);

			window.swapBuffers();
			glfwPollEvents();
		}
	} catch(const std::bad_alloc & e) {
		std::cout << e.what() << std::endl;
		throw e;
	}

	

	return 0;
}