#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera {
private:
	GLFWwindow* window;

	GLuint UBO;
	const glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f,
		0.1f, 2000.0f);
	// Makes View Matrix
	glm::mat4 view;
	glm::vec3 pos{ 0, 0, 0 };
	glm::vec3 front;
	const glm::vec3 up{ 0, 1, 0 };

	double prevTime = glfwGetTime();
	const float baseSpeed = 10;
	const double sensitivity = 0.1;

	double yaw = -90;
	double pitch = 0;
	double prevX = 800 / 2, prevY = 600 / 2;
	bool enabled = true;
public:
	Camera(GLFWwindow* window);
	void update();
	void updateMousePos(double x, double y);
	void enable() { enabled = true; glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); };
	void disable() { enabled = false; glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); };
};

