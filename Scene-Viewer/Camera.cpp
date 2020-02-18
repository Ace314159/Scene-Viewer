#include "stdafx.h"
#include "Camera.h"

#include <glm/gtx/string_cast.hpp>

Camera::Camera(GLFWwindow* window) : window(window) {
	glfwSetWindowUserPointer(window, this);
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
		((Camera*)glfwGetWindowUserPointer(window))->updateMousePos(x, y);
		});
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
		if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
			Camera* camera= (Camera*)glfwGetWindowUserPointer(window);
			camera->enable();
		}
		});

	glGenBuffers(1, &UBO);

	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4) + sizeof(glm::vec3), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));

	glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBO, 0, 2 * sizeof(glm::mat4) + sizeof(glm::vec3));
	enable();
}

void Camera::update() {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		disable();
		return;
	}
	if(!enabled) return;

	double curTime = glfwGetTime();
	double deltaTime = curTime - prevTime;
	prevTime = curTime;
	float speed = float(baseSpeed * deltaTime);

	glm::vec3 dPos(0, 0, 0);
	glm::vec3 front0Y = glm::normalize(glm::vec3(front.x, 0, front.z));
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) dPos += front0Y * speed;
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) dPos -= front0Y * speed;
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		dPos -= glm::normalize(glm::cross(front0Y, up)) * speed;
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		dPos += glm::normalize(glm::cross(front0Y, up)) * speed;
	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		dPos += up * speed;
	if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		dPos -= up * speed;

	pos += dPos;

	view = glm::lookAt(pos, pos + front, up);

	subUniformBuffer buffer = { view, pos };
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(subUniformBuffer), &buffer);
}

void Camera::updateMousePos(double x, double y) {
	double dX = (x - prevX) * sensitivity;
	double dY = -(y - prevY) * sensitivity; // Negative since y values increase from top to bottom
	prevX = x;
	prevY = y;
	if(!enabled) return;

	yaw += dX;
	pitch += dY;
	if(pitch > 89) pitch = 89;
	else if(pitch < -89) pitch = -89;

	front = glm::normalize(glm::vec3(
		cos(glm::radians(pitch)) * cos(glm::radians(yaw)),
		sin(glm::radians(pitch)),
		cos(glm::radians(pitch)) * sin(glm::radians(yaw))
	));
}

void Camera::updateWindowSize(double width, double height) {
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 2000.0f);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
}
