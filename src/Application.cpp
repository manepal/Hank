#include "Application.h"

#include <iostream>
#include <sstream>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Sprite.h"


const float MAX_FPS = 1000.0f;

Sprite marioSprite;
Sprite coinSprite;

// ------------- animation prototyping ----------
const int NUM_SPRITES = 16;

Sprite coinSprites[NUM_SPRITES];
float animationinterval = 0.05f;

int currentFrame = 0;
// ----------------------------------------------

glm::vec3 marioPos = glm::vec3(0.0f);
glm::vec3 coinPos = glm::vec3(0.0f);
const float MOVE_SPEED = 10.0f;
const float ZOOM_SPEED = 2.0f;


Application::Application(const std::string& appTitle, int windowWidth, int windowHeight, bool fullscreen):
	mAppTitle(appTitle),
	mWindowWidth(windowWidth),
	mWindowHeight(windowHeight),
	mIsFullscreen(fullscreen)
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

	if (!Window::getInstance()->initialize(mAppTitle, mWindowWidth, mWindowHeight, mIsFullscreen))
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
	while (!glfwWindowShouldClose(Window::getInstance()->getWindowHandle()))
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
	glfwTerminate();
}

void Application::loadResources()
{
	mShaderProgram.loadShaders("shaders/shader.vert.glsl", "shaders/shader.frag.glsl");
	marioSprite.load("textures/mario.png");
	coinSprite.load("textures/coin.png");

	// ------------- animation prototyping ----------
	for (int i = 0; i < NUM_SPRITES; i++)
	{
		int imageNumber = i + 1;
		std::string imagePath = "textures/coin_animation/image_" + std::to_string(imageNumber) + ".png";
		coinSprites[i].load(imagePath);
	}
	// ----------------------------------------------
}

void Application::update(double dt)
{
	/*
	- control player movement with directional keys.
	UP

	LEFT  DOWN  RIGHT
	*/
	if (glfwGetKey(Window::getInstance()->getWindowHandle(), GLFW_KEY_RIGHT) == GLFW_PRESS) marioPos.x += MOVE_SPEED * dt;
	else if (glfwGetKey(Window::getInstance()->getWindowHandle(), GLFW_KEY_LEFT) == GLFW_PRESS) marioPos.x -= MOVE_SPEED * dt;

	if (glfwGetKey(Window::getInstance()->getWindowHandle(), GLFW_KEY_UP) == GLFW_PRESS) marioPos.y += MOVE_SPEED * dt;
	else if (glfwGetKey(Window::getInstance()->getWindowHandle(), GLFW_KEY_DOWN) == GLFW_PRESS) marioPos.y -= MOVE_SPEED * dt;

	/*
	- control camera movement with WASD keys.
	W
	A S D
	- zoom camera with
	l-shift
	l-ctrl
	*/
	if (glfwGetKey(Window::getInstance()->getWindowHandle(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) mCamera.setFOV(mCamera.getFOV() - ZOOM_SPEED * dt);
	else if (glfwGetKey(Window::getInstance()->getWindowHandle(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) mCamera.setFOV(mCamera.getFOV() + ZOOM_SPEED * dt);

	if (glfwGetKey(Window::getInstance()->getWindowHandle(), GLFW_KEY_W) == GLFW_PRESS) mCamera.move(0.0f, -MOVE_SPEED * dt);
	else if (glfwGetKey(Window::getInstance()->getWindowHandle(), GLFW_KEY_S) == GLFW_PRESS) mCamera.move(0.0f, MOVE_SPEED * dt);

	if (glfwGetKey(Window::getInstance()->getWindowHandle(), GLFW_KEY_A) == GLFW_PRESS) mCamera.move(MOVE_SPEED * dt, 0.0f);
	else if (glfwGetKey(Window::getInstance()->getWindowHandle(), GLFW_KEY_D) == GLFW_PRESS) mCamera.move(-MOVE_SPEED * dt, 0.0f);



	// ---------- animation prototyping ----------
	static float previousTime = glfwGetTime();
	float currentTime = glfwGetTime();
	float elapsedTime = currentTime - previousTime;
	if (elapsedTime >= animationinterval)
	{
		currentFrame++;
		currentFrame %= NUM_SPRITES;
		previousTime = currentTime;
	}
	// -------------------------------------------
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
	//  calculate scale for coin sprites
	float scaleX = coinSprites[currentFrame].getWidth() / (float)coinSprites[currentFrame].getHeight();
	
	model = glm::translate(model, coinPos) * glm::scale(model, glm::vec3(scaleX, 1.0f, 1.0f));
	view = mCamera.getViewMatrix();
	projection = mCamera.getPerspective((float)Window::getInstance()->getWidth(), (float)Window::getInstance()->getHeight());

	mShaderProgram.use();
	mShaderProgram.setUniform("model", model);
	mShaderProgram.setUniform("view", view);
	mShaderProgram.setUniform("projection", projection);

	/*for (int i = 0; i < 1000; i++)
	{
		coinSprite.draw();
	}*/

	// ---------- animation prototyping ----------
	coinSprites[currentFrame].draw();
	// -------------------------------------------


	// now draw mario sprite
	model = glm::translate(glm::mat4(), marioPos);

	mShaderProgram.setUniform("model", model);

	marioSprite.draw();

	mShaderProgram.unUse();
	glfwSwapBuffers(Window::getInstance()->getWindowHandle());
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

		Window::getInstance()->appendTitle(outs.str());

		lastPrint = currentTime;
	}
}
