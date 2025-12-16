#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>
template<typename T>
void DrawTriangle(const std::vector<T>& vertices) {

}
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

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW\n";
		glfwTerminate();
		return -1;
	}

	std::string vertexShaderSource = R"(
		#version 330 core
		layout (location = 0) in vec3 position;
		layout (location = 1) in vec3 color;
		
		out vec3 vColor;		

		void main()
		{
			vColor = color;
			gl_Position = vec4(position.x, position.y, position.z, 1.0);
		}
	)";

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexShaderSCStr = vertexShaderSource.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderSCStr, nullptr);
	glCompileShader(vertexShader);

	GLint success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char log[512];
		glGetShaderInfoLog(vertexShader, 512, nullptr, log);
		std::cerr << "Vertex shader compilation failer" << log << "\n";
	}
	std::string fragmentShaderSource = R"(
		#version 330 core
		out vec4 FragColor;

		in vec3 vColor;
		uniform vec4 uColor;

		void main()
		{
			FragColor = vec4(vColor, 1.0) * uColor;
		}	
	)";

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentShaderSourceCStr = fragmentShaderSource.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderSourceCStr, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char log[512];
		glGetShaderInfoLog(fragmentShader, 512, nullptr, log);
		std::cerr << "Fragment shader compilation failed" << log << "\n";
	}

	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		char log[512];
		glGetProgramInfoLog(shaderProgram, 512, nullptr, log);
		std::cerr << "Shader program linking failure" << log << "\n";
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	std::vector<float> vertices = {
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f ,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f
	};
	std::vector<unsigned int> indices{
		0, 1, 2,
		0, 2, 3,
	};
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	GLint uColorLoc = glGetUniformLocation(shaderProgram, "uColor");


	while (!glfwWindowShouldClose(window)) {
		glClearColor(1.0f, 1.0f, 0.32f, 3.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glUniform4f(uColorLoc, 0.0f, 1.0f, 0.44f, 1.0f);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
