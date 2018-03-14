#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <iostream>

#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Camera.h"

GLFWwindow* gWindow;
const char* APP_TITLE = "Hank";
const int WIDTH = 1080;
const int HEIGHT = 768;

GLuint vbo = 0;
GLuint ibo = 0;
GLuint vao = 0;

ShaderProgram gShaderProgram;
const std::string hankTexturePath = "textures/jump.png";
Texture2D hankTexture;
const std::string coinTexturePath = "textures/coin.png";
Texture2D coinTexture;

Camera gCamera;

glm::vec3 spritePos = glm::vec3(0.0f);
const float MOVE_SPEED = 0.05f;

bool init();
void mainLoop();
void cleanup();

void initVertices();
void update(float dt);
void draw();

int main()
{
	if (!init())
	{
		cleanup();
		return -1;
	}

	initVertices();

	gShaderProgram.loadShaders("shaders/shader.vert.glsl", "shaders/shader.frag.glsl");
	hankTexture.loadTexture(hankTexturePath);
	coinTexture.loadTexture(coinTexturePath);
	
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
		update(0.05f);
		draw();
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
		// position	 // texture coordinates
		-1.0f, 1.0f, 0.0f, 1.0f,	// top left
		 1.0f, 1.0f, 0.5f, 1.0f,	// top right
		 1.0f,-1.0f, 0.5f, 0.0f,	// bottom right
		-1.0f,-1.0f, 0.0f, 0.0f		// bottom left
	};

	GLushort indices[] = {
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
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(0);


	// texcoords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(1, 0);
	glBindVertexArray(0);
}

void update(float dt)
{
	/*
		- control player movement with directional keys.
					UP

			 LEFT  DOWN  RIGHT
	*/
	if (glfwGetKey(gWindow, GLFW_KEY_RIGHT) == GLFW_PRESS) spritePos.x += MOVE_SPEED * dt;
	else if (glfwGetKey(gWindow, GLFW_KEY_LEFT) == GLFW_PRESS) spritePos.x -= MOVE_SPEED * dt;

	if (glfwGetKey(gWindow, GLFW_KEY_UP) == GLFW_PRESS) spritePos.y += MOVE_SPEED * dt;
	else if (glfwGetKey(gWindow, GLFW_KEY_DOWN) == GLFW_PRESS) spritePos.y -= MOVE_SPEED * dt;

	/*
		- control camera movement with WASD keys.
					W
				  A S D
		- zoom camera with
			l-shift
			l-ctrl
	*/
	if (glfwGetKey(gWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) gCamera.setFOV(gCamera.getFOV() - 0.05f * dt);
	else if (glfwGetKey(gWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) gCamera.setFOV(gCamera.getFOV() + 0.05f * dt);

	if (glfwGetKey(gWindow, GLFW_KEY_W) == GLFW_PRESS) gCamera.move(0.0f, -MOVE_SPEED * dt);
	else if (glfwGetKey(gWindow, GLFW_KEY_S) == GLFW_PRESS) gCamera.move(0.0f, MOVE_SPEED * dt);
	
	if (glfwGetKey(gWindow, GLFW_KEY_A) == GLFW_PRESS) gCamera.move(MOVE_SPEED * dt, 0.0f);
	else if (glfwGetKey(gWindow, GLFW_KEY_D) == GLFW_PRESS) gCamera.move(-MOVE_SPEED * dt, 0.0f);
}

void draw()
{
	glClearColor(0.0f, 0.5f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	model = glm::translate(model, glm::vec3(0.0f));
	view = gCamera.getViewMatrix();
	projection = gCamera.getProjectionMatrix((float)WIDTH, (float)HEIGHT);

	glBindVertexArray(vao);

	//glDrawArrays(GL_LINE_LOOP, 0, 4);

	gShaderProgram.use();

	gShaderProgram.setUniform("model", model);
	gShaderProgram.setUniform("view", view);
	gShaderProgram.setUniform("projection", projection);

	coinTexture.bind(0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

	coinTexture.unbind(0);
	hankTexture.bind(0);


	model = glm::translate(glm::mat4(), spritePos);

	gShaderProgram.setUniform("model", model);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

	hankTexture.unbind(0);
	glBindVertexArray(0);

	glfwSwapBuffers(gWindow);
}