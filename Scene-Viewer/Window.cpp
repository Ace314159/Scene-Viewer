#include "stdafx.h"
#include "Window.h"

Window::Window() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 600, "Model Viewer", nullptr, nullptr);
	if(window == nullptr) {
		throw std::runtime_error("Failed to create GLFW window!");
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to initialize GLAD");
	}

#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(glDebugCallback, nullptr);
	GLuint ignoredIDs[] = { 0x20071 };
	glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_OTHER, GL_DONT_CARE, 1, ignoredIDs, GL_FALSE);
	glfwSetErrorCallback([](int errorCode, const char* desc) {
		char error[255];
		sprintf_s(error, "GLFW Error %d: %s\n", errorCode, desc);
		throw std::runtime_error(error);
	});
#endif
	
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	});
}

Window::~Window() {
	glfwTerminate();
}
