#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {

	if (!glfwInit()) {
		std::cerr << "Error";
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1280, 720, "SasoEngine", nullptr, nullptr);
	
	if (window == nullptr) {
		std::cerr << "Error creating window";
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 300, 300);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return -1;
	}

	while (!glfwWindowShouldClose(window)) {
		glClearColor(1.0f, 1.0f, 1.0f,0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
