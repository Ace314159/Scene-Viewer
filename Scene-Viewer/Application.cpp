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
		Shader phong("phong");
		Shader pbr("pbr");

		glm::vec3 lightPos(0, 5, 0);
		glm::vec3 lightColor(1, 1, 1);

		pbr.use();
		pbr.setVec3("albedo", glm::vec3(0.5, 0, 0));
		pbr.setFloat("ao", 1);
		pbr.setFloat("metallic", 0.5);
		pbr.setFloat("roughness", 0.5);
		pbr.setVec3("lightPos", lightPos);
		pbr.setVec3("lightColor", lightColor);

		while(window.isOpen()) {
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			camera.update();
			model.draw(phong);
			sphere.draw(pbr);

			window.swapBuffers();
			glfwPollEvents();
		}
	} catch(const std::bad_alloc & e) {
		std::cout << e.what() << std::endl;
		throw e;
	}

	

	return 0;
}