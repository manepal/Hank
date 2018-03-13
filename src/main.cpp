#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>


#include <iostream>

#include "ShaderProgram.h"


GLFWwindow* gWindow;
const char* APP_TITLE = "Hank";
const int WIDTH = 1080;
const int HEIGHT = 768;

GLuint vbo = 0;
GLuint ibo = 0;
GLuint vao = 0;

ShaderProgram gShaderProgram;

bool init();
void mainLoop();
void cleanup();

void initVertices();
void draw();

int main()
{
	if (!init())
	{
		cleanup();
		return -1;
	}

	initVertices();

	gShaderProgram.loadShaders("shaders/basic.vert.glsl", "shaders/basic.frag.glsl");
	
	mainLoop();
	cleanup();

	return 0;
}

bool init()
{
	if (!glfwInit())
	{
		std::cerr << "failed to initialize GLFW!" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	gWindow = glfwCreateWindow(WIDTH, HEIGHT, APP_TITLE, nullptr, nullptr);
	if (gWindow == nullptr)
	{
		std::cerr << "failed to create window!" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(gWindow);

	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		std::cerr << "failed to initialize GLEW!" << std::endl;
		return false;
	}

	return true;
}

void mainLoop()
{
	while (!glfwWindowShouldClose(gWindow))
	{
		glfwPollEvents();
		draw();
		glfwSwapBuffers(gWindow);
	}
}

void cleanup()
{
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	glDeleteVertexArrays(1, &vao);

	vbo = 0;
	ibo = 0;
	vao = 0;

	if (gWindow != nullptr)
	{
		glfwDestroyWindow(gWindow);
	}

	glfwTerminate();
}

void initVertices()
{
	GLfloat vertices[] = {
		// position		// color
		-0.5f, 0.5f, 1.0f, 0.0f, 0.0f,	// top left
		 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,	// top right
		 0.5f,-0.5f, 0.0f, 0.0f, 1.0f,	// bottom right
		-0.5f,-0.5f, 1.0f, 1.0f, 0.0f	// bottom left
	};

	GLuint indices[] = {
		0, 1, 2,	// first triangle
		2, 3, 0		// secont triangle
	};

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(1, 0);
	glBindVertexArray(0);
}

void draw()
{
	glBindVertexArray(vao);
	gShaderProgram.use();

	float time = glfwGetTime();

	gShaderProgram.setUniform("time", time);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}