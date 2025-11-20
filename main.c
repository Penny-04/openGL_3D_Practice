#include "stdio.h"
#include "stdlib.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLFWwindow* window; 

void create_triangle() {
	// Define vertices of a triangle
	float vertices[] = {
    		-0.5f, -0.5f, 0.0f,
    		0.5f, -0.5f, 0.0f,
    		0.0f, 0.5f, 0.0f
	};

	// Create a vertex buffer object (VBO)
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	const char *vertexShaderSource = "#version 330 core\n"
    		"layout (location = 0) in vec3 aPos;\n"
    		"void main()\n"
    		"{\n"
    		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    		"}\0";

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Create a vertex array object (VAO)
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Main rendering loop
	while (!glfwWindowShouldClose(window)) {
    		glClear(GL_COLOR_BUFFER_BIT);

    		// Render triangle
    		glDrawArrays(GL_TRIANGLES, 0, 3);

    		glfwSwapBuffers(window);
    		glfwPollEvents();
	}

}

int main(int argc, int argv) {
	printf("Initialising openGL\n");
	// Initialize GLFW
    	if (!glfwInit()) { 
		printf("glfw failed to initialise\n");	
		return -1;
    	}

    	// Create a window
    	window = glfwCreateWindow(800, 600, "3D Rendering Engine", NULL, NULL);
    	if (!window) {
		printf("Window creation failed\n");
        	glfwTerminate();
        	return -1;
    	}

    	// Main loop
	create_triangle();
	// Clean up
    	glfwDestroyWindow(window);
    	glfwTerminate();
    	return 0;
}
