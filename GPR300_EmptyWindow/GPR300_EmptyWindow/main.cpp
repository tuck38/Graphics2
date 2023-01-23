#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <stdio.h>

//void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void resizeFrameBufferCallback(GLFWwindow* window, int width, int height);

const char* vertexShaderSource =
"#version 450                      \n"
"layout(location = 0) in vec3 vPos; \n"
"void main(){                      \n"
"     gl_Position = vec4(vPos,1.0);\n"
"}                                 \0";

const char* fragmentShaderSource = 
"#version 450                      \n"
"out vec4 FragColor;               \n"
"void main(){                      \n"
"   FragColor = vec4(1.0);         \n"
"}                                 \0";

//Vertex data array
const float vertexData[] = 
{ 
	//x   //y   //z
    +0.0, +0.0, +0.0,
	+0.2, +0.7, +0.0,
	+0.6, +0.5, +0.0
};

int main() {
	if (!glfwInit()) {
		printf("glfw failed to init");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGLExample", 0, 0);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		printf("glew failed to init");
		return 1;
	}

	glfwSetFramebufferSizeCallback(window, resizeFrameBufferCallback);


	//Create and compile vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//Get vertex shader compilation status and output info log
	GLint success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("Failed to compile vertex shader: %s", infoLog);
	}
	
	//Create and compile fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Get fragment shader compilation status and output info log
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("Failed to compile fragment shader: %s", infoLog);
	}

	//Create shader program
	GLuint shaderProgram = glCreateProgram();

	//Attach vertex and fragment shaders to shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	//Link shader program
	glLinkProgram(shaderProgram);

	//TODO: Check for link status and output errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("Failed to link shader program %s", infoLog);
	}

	//Delete vertex + fragment shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Create and bind Vertex Array Object (VAO)
	
	unsigned int vertexArrayObject;

	//create
	glGenVertexArrays(1, &vertexArrayObject);

	//bind
    glBindVertexArray(vertexArrayObject);

	//Create and bind Vertex Buffer Object (VBO), fill with vertexData
	
	//generate a buffer with id
	unsigned int vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);

	//bind the new buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

	//create new data store
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	//Define vertex attribute layout
	
	//tells the shader to definre the VBO as three vec3's
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (const void*)0);

	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Use shader program
		glUseProgram(shaderProgram);
		
		//Draw triangle (3 indices!)
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void resizeFrameBufferCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

