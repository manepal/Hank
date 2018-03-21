#include "Application.h"

#include <iostream>
#include <sstream>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <Buzz\Animation.h>
#include <Buzz\AnimationController.h>

BUZZ::Sprite marioSprite;
BUZZ::Sprite coinSprite;

// ----------------- animation ------------------
BUZZ::AnimationController animController;
std::shared_ptr<BUZZ::Animation> switchAnimation(new BUZZ::Animation(0.5f));
std::shared_ptr<BUZZ::Animation> flagAnimation(new BUZZ::Animation(0.25f));
std::shared_ptr<BUZZ::Animation> flyAnimation(new BUZZ::Animation(0.125f));
std::shared_ptr<BUZZ::Animation> coninAnimation(new BUZZ::Animation(0.05f));


glm::vec3 marioPos = glm::vec3(0.0f);
glm::vec3 coinPos = glm::vec3(0.0f);
const float MOVE_SPEED = 100.0f;
const float ZOOM_SPEED = 50.0f;


Application::Application()
{
	mAppTitle = "Adventure of Hank";
	mWindowWidth = 1366;
	mWindowHeight = 720;
	mIsFullscreen = false;
}

void Application::startup()
{
	mShaderProgram.loadShaders("shaders/shader.vert.glsl", "shaders/shader.frag.glsl");
	marioSprite.load("textures/mario.png");
	coinSprite.load("textures/coin.png");

	switchAnimation->addFrame("textures/animation/switchLeft.png");
	switchAnimation->addFrame("textures/animation/switchMid.png");
	switchAnimation->addFrame("textures/animation/switchRight.png");
	switchAnimation->addFrame("textures/animation/switchMid.png");

	flagAnimation->addFrame("textures/animation/flagRed.png");
	flagAnimation->addFrame("textures/animation/flagRed2.png");

	flyAnimation->addFrame("textures/animation/flyFly1.png");
	flyAnimation->addFrame("textures/animation/flyFly2.png");

	for (int i = 0; i < 16; i++)
	{
		std::string imagePath = "textures/animation/coin_" + std::to_string(i) + ".png";
		coninAnimation->addFrame(imagePath);
	}

	animController.addAnimation("coin", coninAnimation);
	animController.addAnimation("switch", switchAnimation);
	animController.addAnimation("fly", flyAnimation);
	animController.addAnimation("flag", flagAnimation);;
}

void Application::update(float dt)
{
	// use I, J, K, L to toggle animation
	if (glfwGetKey(BUZZ::Window::getInstance()->getWindowHandle(), GLFW_KEY_I) == GLFW_PRESS) animController.setActiveAnimation("coin");
	if (glfwGetKey(BUZZ::Window::getInstance()->getWindowHandle(), GLFW_KEY_J) == GLFW_PRESS) animController.setActiveAnimation("switch");
	if (glfwGetKey(BUZZ::Window::getInstance()->getWindowHandle(), GLFW_KEY_K) == GLFW_PRESS) animController.setActiveAnimation("flag");
	if (glfwGetKey(BUZZ::Window::getInstance()->getWindowHandle(), GLFW_KEY_L) == GLFW_PRESS) animController.setActiveAnimation("fly");

	/*
	- control player movement with directional keys.
	UP

	LEFT  DOWN  RIGHT
	*/
	if (glfwGetKey(BUZZ::Window::getInstance()->getWindowHandle(), GLFW_KEY_RIGHT) == GLFW_PRESS) marioPos.x += MOVE_SPEED * dt;
	else if (glfwGetKey(BUZZ::Window::getInstance()->getWindowHandle(), GLFW_KEY_LEFT) == GLFW_PRESS) marioPos.x -= MOVE_SPEED * dt;

	if (glfwGetKey(BUZZ::Window::getInstance()->getWindowHandle(), GLFW_KEY_UP) == GLFW_PRESS) marioPos.y += MOVE_SPEED * dt;
	else if (glfwGetKey(BUZZ::Window::getInstance()->getWindowHandle(), GLFW_KEY_DOWN) == GLFW_PRESS) marioPos.y -= MOVE_SPEED * dt;

	/*
	- control camera movement with WASD keys.
	W
	A S D
	- zoom camera with
	l-shift
	l-ctrl
	*/
	if (glfwGetKey(BUZZ::Window::getInstance()->getWindowHandle(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) mCamera.zoom(-ZOOM_SPEED * dt);
	else if (glfwGetKey(BUZZ::Window::getInstance()->getWindowHandle(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) mCamera.zoom(ZOOM_SPEED * dt);;

	if (glfwGetKey(BUZZ::Window::getInstance()->getWindowHandle(), GLFW_KEY_W) == GLFW_PRESS) mCamera.move(0.0f, -MOVE_SPEED * dt);
	else if (glfwGetKey(BUZZ::Window::getInstance()->getWindowHandle(), GLFW_KEY_S) == GLFW_PRESS) mCamera.move(0.0f, MOVE_SPEED * dt);

	if (glfwGetKey(BUZZ::Window::getInstance()->getWindowHandle(), GLFW_KEY_A) == GLFW_PRESS) mCamera.move(MOVE_SPEED * dt, 0.0f);
	else if (glfwGetKey(BUZZ::Window::getInstance()->getWindowHandle(), GLFW_KEY_D) == GLFW_PRESS) mCamera.move(-MOVE_SPEED * dt, 0.0f);

	// update the animation controller
	animController.update(dt);
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
	//float scaleX = coinSprites[currentFrame].getWidth() / (float)coinSprites[currentFrame].getHeight();
	
	model = glm::translate(model, coinPos);
	view = mCamera.getViewMatrix();
	projection = mCamera.getOrtho();

	mShaderProgram.use();
	mShaderProgram.setUniform("model", model);
	mShaderProgram.setUniform("view", view);
	mShaderProgram.setUniform("projection", projection);

	/*
	for (int i = 0; i < 1000; i++)
	{
		coinSprite.draw();
	}
	*/

	//coinSprite.draw();

	// ---------- animation ----------
	animController.draw();
	

	//// now draw mario sprite
	//model = glm::translate(glm::mat4(), marioPos);

	//mShaderProgram.setUniform("model", model);

	//marioSprite.draw();

	mShaderProgram.unUse();
	glfwSwapBuffers(BUZZ::Window::getInstance()->getWindowHandle());
}

void Application::shutdown()
{
}