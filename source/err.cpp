#include <iostream>
#include <GLFW/glfw3.h>
#include <string>
#include <GL/glew.h>

void printShaderLog(GLuint shader) {
	int len{};
	int chWritten{};
	char* log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = static_cast<char*>(malloc(len));
		glGetShaderInfoLog(shader, GL_INFO_LOG_LENGTH, &chWritten, log);
		std::cout << log << "\n";
		free(log);
	}
}
void printProgramLog(int program) {
	int len{};
	int chWritten{};
	char* log;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = static_cast<char*>(malloc(len));
		glGetProgramInfoLog(program, len, &chWritten, log);
		std::cout << log << "\n";
		free(log);
	}
}
bool checkGLError() {
	bool err = false;
	int GLerror = glGetError();
	while (GLerror != GL_NO_ERROR) {
		std::cout << GLerror << "\n";
		err = true;
		GLerror = glGetError();
	}
	return err;
}