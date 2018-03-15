#include "Application.h"

#include <iostream>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Sprite.h"
Sprite marioSprite("textures/mario.png");
Sprite coinSprite("textures/coin.png");

glm::vec3 marioPos = glm::vec3(0.0f);
glm::vec3 coinPos = glm::vec3(0.0f);
const float MOVE_SPEED = 0.05f;


Application::Application(const std::string& appTitle, int windowWidth, int windowHeight):
	mAppTitle(appTitle),
	mWindowWidth(windowWidth),
	mWindowHeight(windowHeight)
{
}

Application::~Application()
{
}

void Application::run()
{
	if (!initialize())
	{
		std::cerr << "failed to initialize application" << std::endl;
		cleanup();
		return;
	}

	loadResources();
	mainLoop();
	cleanup();
}

bool Application::initialize()
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


	mWindow = glfwCreateWindow(mWindowWidth, mWindowHeight, mAppTitle.c_str(), nullptr, nullptr);
	if (mWindow == nullptr)
	{
		std::cerr << "failed to create window!" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(mWindow);

	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		std::cerr << "failed to initialize GLEW!" << std::endl;
		return false;
	}

	return true;
}

void Application::mainLoop()
{
	while (!glfwWindowShouldClose(mWindow))
	{
		glfwPollEvents();
		update(0.1);
		draw();
	}
}

void Application::cleanup()
{
	if (mWindow != nullptr)
	{
		glfwDestroyWindow(mWindow);
		mWindow = nullptr;
	}

	glfwTerminate();
}

void Application::loadResources()
{
	mShaderProgram.loadShaders("shaders/shader.vert.glsl", "shaders/shader.frag.glsl");
	marioSprite.load();
	coinSprite.load();
}

void Application::update(float dt)
{
	if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(mWindow, GL_TRUE);
	}

	/*
	- control player movement with directional keys.
	UP

	LEFT  DOWN  RIGHT
	*/
	if (glfwGetKey(mWindow, GLFW_KEY_RIGHT) == GLFW_PRESS) marioPos.x += MOVE_SPEED * dt;
	else if (glfwGetKey(mWindow, GLFW_KEY_LEFT) == GLFW_PRESS) marioPos.x -= MOVE_SPEED * dt;

	if (glfwGetKey(mWindow, GLFW_KEY_UP) == GLFW_PRESS) marioPos.y += MOVE_SPEED * dt;
	else if (glfwGetKey(mWindow, GLFW_KEY_DOWN) == GLFW_PRESS) marioPos.y -= MOVE_SPEED * dt;

	/*
	- control camera movement with WASD keys.
	W
	A S D
	- zoom camera with
	l-shift
	l-ctrl
	*/
	if (glfwGetKey(mWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) mCamera.setFOV(mCamera.getFOV() - 0.05f * dt);
	else if (glfwGetKey(mWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) mCamera.setFOV(mCamera.getFOV() + 0.05f * dt);

	if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS) mCamera.move(0.0f, -MOVE_SPEED * dt);
	else if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS) mCamera.move(0.0f, MOVE_SPEED * dt);

	if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS) mCamera.move(MOVE_SPEED * dt, 0.0f);
	else if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS) mCamera.move(-MOVE_SPEED * dt, 0.0f);
}

void Application::draw()
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
	view = mCamera.getViewMatrix();
	projection = mCamera.getPerspective((float)mWindowWidth, (float)mWindowHeight);

	mShaderProgram.use();
	mShaderProgram.setUniform("model", model);
	mShaderProgram.setUniform("view", view);
	mShaderProgram.setUniform("projection", projection);

	coinSprite.draw();

	// now draw mario sprite
	model = glm::translate(glm::mat4(), marioPos);

	mShaderProgram.setUniform("model", model);

	marioSprite.draw();

	glfwSwapBuffers(mWindow);
}
