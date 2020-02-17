#include "stdafx.h"
#include "Camera.h"
#include "Mesh.h"
#include "Model.h"
#include "Shader.h"
#include "Window.h"

int main() {
	try {
		Window window;

		Camera camera(window.window);

		Mesh::initVAO();
		//Model model("nanosuit/nanosuit.obj");
		Shader shader("solidColor");
		Mesh mesh({
			{{-0.5, -0.5, 1}, {0, 0, 0}, {0, 0}},
			{{ 0.5, -0.5, 1}, {0, 0, 0}, {0, 0}},
			{{ 0.0,  0.5, 1}, {0, 0, 0}, {0, 0}},
		}, {0, 1, 2}, {});

		while(window.isOpen()) {
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			camera.update();
			shader.use();
			mesh.draw(shader);

			window.swapBuffers();
			glfwPollEvents();
		}
	} catch(const std::exception & e) {
		std::cout << e.what() << std::endl;
		throw e;
	}

	

	return 0;
}