#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

float vertices[] = {
	0.5f, 0.5f, 0.0f, // top right
	0.5f, -0.5f, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f, // bottom left
	-0.5f, 0.5f, 0.0f, // top left
	0.0f, 0.5f, 0.0f, // top middle
	0.0f, -0.5f, 0.0f // bottom middle
};

unsigned int indices[] = { // note that we start from 0!
	1, 5, 4, // first triangle
	2, 5, 4 // second triangle
};

float left_triangle[] = {
	0.5f, -0.5f, 0.0f, 
	0.0f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};

float right_triangle[] = {
	-0.5f, -0.5f, 0.0f, 
	0.0f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};

const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	" FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";


const char *fragmentShaderSource_yellow = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	" FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
	"}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	printf("Starting\n");
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD\n");
		return -1;
	}	
	
	glViewport(0, 0, 800, 600);	
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success) {
		//glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();


	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glUseProgram(shaderProgram);
	
	unsigned int fragmentShader_yellow;
	fragmentShader_yellow = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_yellow, 1, &fragmentShaderSource_yellow, NULL);
	glCompileShader(fragmentShader_yellow);

	unsigned int shaderProgram_yellow;
	shaderProgram_yellow = glCreateProgram();

	glAttachShader(shaderProgram_yellow, vertexShader);
	glAttachShader(shaderProgram_yellow, fragmentShader_yellow);
	glLinkProgram(shaderProgram_yellow);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	


	unsigned int VBOs[2], VAOs[2]; //, EBO;
	//Reminder!
	// VBO stands for Vertex Buffer Object
	// A VBO is GPU memory that stores vertex data (positions, normals, colors, texture coords…)
	// VAO stands for Vertex Array Object
	// A VAO stores the state describing how vertex data is laid out.
	// EBO stands for Element Buffer Object
	// Stores indices—integer references to vertices in the VBO. Allows you to reuse vertices instead of duplicating them (useful for drawing triangles efficiently).

    	glGenVertexArrays(2, VAOs);
    	glGenBuffers(2, VBOs);

    	//glGenBuffers(1, &EBO);
    	
	//Work Begins!
	
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(left_triangle), left_triangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

    	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(right_triangle), right_triangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	
	while(!glfwWindowShouldClose(window)) {
		//Process any keyboard inputs
		processInput(window);
	
		//Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		//Draw our triangles
		glUseProgram(shaderProgram);

	        glBindVertexArray(VAOs[0]);
        	glDrawArrays(GL_TRIANGLES, 0, 3);
        	// then we draw the second triangle using the data from the second VAO
        	glUseProgram(shaderProgram_yellow);

		glBindVertexArray(VAOs[1]);
        	glDrawArrays(GL_TRIANGLES, 0, 3);
		
		//Swap buffers and poll for keyboard inputs
		glfwSwapBuffers(window);
		glfwPollEvents();
	}	
	glfwTerminate();	
	return 0;
}
