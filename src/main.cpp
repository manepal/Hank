#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <iostream>

#include "ShaderProgram.h"
#include "Sprite.h"
#include "Camera.h"

GLFWwindow* gWindow;
const char* APP_TITLE = "Hank";
const int WIDTH = 1080;
const int HEIGHT = 768;

ShaderProgram gShaderProgram;
Sprite marioSprite("textures/mario.png");
Sprite coinSprite("textures/coin.png");

Camera gPerspectiveCamera;

glm::vec3 marioPos = glm::vec3(0.0f);
glm::vec3 coinPos = glm::vec3(0.0f);
const float MOVE_SPEED = 0.05f;

bool init();
void mainLoop();
void cleanup();

void update(float dt);
void draw();

int main()
{
	if (!init())
	{
		cleanup();
		return -1;
	}

	gShaderProgram.loadShaders("shaders/shader.vert.glsl", "shaders/shader.frag.glsl");
	marioSprite.load();
	coinSprite.load();

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
	if (gWindow != nullptr)
	{
		glfwDestroyWindow(gWindow);
	}

	glfwTerminate();
}

void update(float dt)
{
	if (glfwGetKey(gWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(gWindow, GL_TRUE);
	}

	/*
		- control player movement with directional keys.
					UP

			 LEFT  DOWN  RIGHT
	*/
	if (glfwGetKey(gWindow, GLFW_KEY_RIGHT) == GLFW_PRESS) marioPos.x += MOVE_SPEED * dt;
	else if (glfwGetKey(gWindow, GLFW_KEY_LEFT) == GLFW_PRESS) marioPos.x -= MOVE_SPEED * dt;

	if (glfwGetKey(gWindow, GLFW_KEY_UP) == GLFW_PRESS) marioPos.y += MOVE_SPEED * dt;
	else if (glfwGetKey(gWindow, GLFW_KEY_DOWN) == GLFW_PRESS) marioPos.y -= MOVE_SPEED * dt;

	/*
		- control camera movement with WASD keys.
					W
				  A S D
		- zoom camera with
			l-shift
			l-ctrl
	*/
	if (glfwGetKey(gWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) gPerspectiveCamera.setFOV(gPerspectiveCamera.getFOV() - 0.05f * dt);
	else if (glfwGetKey(gWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) gPerspectiveCamera.setFOV(gPerspectiveCamera.getFOV() + 0.05f * dt);

	if (glfwGetKey(gWindow, GLFW_KEY_W) == GLFW_PRESS) gPerspectiveCamera.move(0.0f, -MOVE_SPEED * dt);
	else if (glfwGetKey(gWindow, GLFW_KEY_S) == GLFW_PRESS) gPerspectiveCamera.move(0.0f, MOVE_SPEED * dt);
	
	if (glfwGetKey(gWindow, GLFW_KEY_A) == GLFW_PRESS) gPerspectiveCamera.move(MOVE_SPEED * dt, 0.0f);
	else if (glfwGetKey(gWindow, GLFW_KEY_D) == GLFW_PRESS) gPerspectiveCamera.move(-MOVE_SPEED * dt, 0.0f);
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

	// first render coin sprite
	model = glm::translate(model, coinPos);
	view = gPerspectiveCamera.getViewMatrix();
	projection = gPerspectiveCamera.getPerspective((float)WIDTH, (float)HEIGHT);

	gShaderProgram.use();
	gShaderProgram.setUniform("model", model);
	gShaderProgram.setUniform("view", view);
	gShaderProgram.setUniform("projection", projection);

	coinSprite.draw();

	// now draw mario sprite
	model = glm::translate(glm::mat4(), marioPos);

	gShaderProgram.setUniform("model", model);
	
	marioSprite.draw();

	glfwSwapBuffers(gWindow);
}