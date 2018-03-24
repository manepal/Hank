#include "HankApplication.h"


HankApplication::HankApplication()
{
	mAppTitle = "Adventure of Hank";
	mWindowWidth = 1366;
	mWindowHeight = 768;
	mIsFullscreen = false;

	mHank = new Player();
}

void HankApplication::startup()
{
	mShaderProgram.loadShaders("shaders/shader.vert.glsl", "shaders/shader.frag.glsl");
	mHank->loadResources();
}

void HankApplication::update(float dt)
{
	mHank->update(dt);
}

void HankApplication::render()
{
	mat4 model = mHank->getModelMatrix();
	mat4 view = mCamera.getViewMatrix();
	mat4 projection = mCamera.getOrtho();
	
	mShaderProgram.use();
	mShaderProgram.setUniform("model", model);
	mShaderProgram.setUniform("view", view);
	mShaderProgram.setUniform("projection", projection);
	mHank->draw();
	mShaderProgram.unUse();
}

void HankApplication::shutdown()
{
	if (mHank)
	{
		delete mHank;
	}
}
