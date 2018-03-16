#include "Application.h"

#include <iostream>
#include <sstream>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Sprite.h"


const float MAX_FPS = 1000.0f;

Sprite marioSprite("textures/mario.png");
Sprite coinSprite("textures/coin.png");

glm::vec3 marioPos = glm::vec3(0.0f);
glm::vec3 coinPos = glm::vec3(0.0f);
const float MOVE_SPEED = 10.0f;
const float ZOOM_SPEED = 2.0f;


Application::Application(const std::string& appTitle, int windowWidth, int windowHeight, bool fullscreen):
	mAppTitle(appTitle),
	mWindowWidth(windowWidth),
	mWindowHeight(windowHeight)
{
	mWindow = new Window(mAppTitle, mWindowWidth, mWindowHeight, fullscreen);
}

Application::~Application()
{
	if (mWindow != nullptr)
	{
		delete mWindow;
		mWindow = nullptr;
	}
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

	if (!mWindow->initialize())
	{
		cleanup();
		return false;
	}

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
	while (!glfwWindowShouldClose(mWindow->getWindowHandle()))
	{
		glfwPollEvents();

		float currentFrameTime = glfwGetTime();

		update(mFrameTime);
		draw();
		showFPS();
	}
}

void Application::cleanup()
{
	delete mWindow;
	mWindow = nullptr;
	glfwTerminate();
}

void Application::loadResources()
{
	mShaderProgram.loadShaders("shaders/shader.vert.glsl", "shaders/shader.frag.glsl");
	marioSprite.load();
	coinSprite.load();
}

void Application::update(double dt)
{
	if (glfwGetKey(mWindow->getWindowHandle(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		mWindow->close();
	}

	/*
	- control player movement with directional keys.
	UP

	LEFT  DOWN  RIGHT
	*/
	if (glfwGetKey(mWindow->getWindowHandle(), GLFW_KEY_RIGHT) == GLFW_PRESS) marioPos.x += MOVE_SPEED * dt;
	else if (glfwGetKey(mWindow->getWindowHandle(), GLFW_KEY_LEFT) == GLFW_PRESS) marioPos.x -= MOVE_SPEED * dt;

	if (glfwGetKey(mWindow->getWindowHandle(), GLFW_KEY_UP) == GLFW_PRESS) marioPos.y += MOVE_SPEED * dt;
	else if (glfwGetKey(mWindow->getWindowHandle(), GLFW_KEY_DOWN) == GLFW_PRESS) marioPos.y -= MOVE_SPEED * dt;

	/*
	- control camera movement with WASD keys.
	W
	A S D
	- zoom camera with
	l-shift
	l-ctrl
	*/
	if (glfwGetKey(mWindow->getWindowHandle(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) mCamera.setFOV(mCamera.getFOV() - ZOOM_SPEED * dt);
	else if (glfwGetKey(mWindow->getWindowHandle(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) mCamera.setFOV(mCamera.getFOV() + ZOOM_SPEED * dt);

	if (glfwGetKey(mWindow->getWindowHandle(), GLFW_KEY_W) == GLFW_PRESS) mCamera.move(0.0f, -MOVE_SPEED * dt);
	else if (glfwGetKey(mWindow->getWindowHandle(), GLFW_KEY_S) == GLFW_PRESS) mCamera.move(0.0f, MOVE_SPEED * dt);

	if (glfwGetKey(mWindow->getWindowHandle(), GLFW_KEY_A) == GLFW_PRESS) mCamera.move(MOVE_SPEED * dt, 0.0f);
	else if (glfwGetKey(mWindow->getWindowHandle(), GLFW_KEY_D) == GLFW_PRESS) mCamera.move(-MOVE_SPEED * dt, 0.0f);
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

	for (int i = 0; i < 1000; i++)
	{
		coinSprite.draw();
	}
	// now draw mario sprite
	model = glm::translate(glm::mat4(), marioPos);

	mShaderProgram.setUniform("model", model);

	marioSprite.draw();

	mShaderProgram.unUse();
	glfwSwapBuffers(mWindow->getWindowHandle());
}

void Application::showFPS()
{
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float previousTime = glfwGetTime();
	
	float currentTime;

	// ---------- limit fps to max fps ----------
	do
	{
		currentTime = glfwGetTime();
		mFrameTime = currentTime - previousTime;
	}
	while (mFrameTime < 1.0f / MAX_FPS);
	// ------------------------------------------

	previousTime = currentTime;

	frameTimes[currentFrame % NUM_SAMPLES] = mFrameTime;
	
	int numFrames;
	currentFrame++;
	if (currentFrame < NUM_SAMPLES)
	{
		numFrames = currentFrame;
	}
	else
	{
		numFrames = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;
	for (int i = 0; i < numFrames; i++)
	{
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage = frameTimeAverage / numFrames;

	if (frameTimeAverage > 0)
	{
		// time  is in seconds divide 1 frame by average time taken to render 1 frame
		mFPS = 1.0f/ frameTimeAverage;
	}
	else
	{
		mFPS = 0.0f;
	}

	// display fps twice every second
	static float lastPrint = currentTime;
	float elapsedTime = currentTime - lastPrint;

	if (elapsedTime >= 0.5f)
	{
		std::ostringstream outs;
		outs.precision(3);
		outs << std::fixed
			<< ": " << mWindowWidth << "x" << mWindowHeight << "    "
			<< "FPS: " << mFPS << "   ";

		mWindow->appendTitle(outs.str());

		lastPrint = currentTime;
	}
}
