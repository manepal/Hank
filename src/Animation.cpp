#include "Animation.h"

#include <GLFW\glfw3.h>

Animation::Animation(float interval) :
	mInterval(interval),
	mCurrentFrameIndex(0),
	mCurrentTime(0.0f)
{
}

Animation::~Animation()
{
	mFrames.clear();
}

void Animation::addFrame(const std::string& texturePath)
{
	std::shared_ptr<Sprite> animFrame (new Sprite);
	animFrame->load(texturePath);

	mFrames.push_back(animFrame);
}

void Animation::setInterval(float interval)
{
	mInterval = interval;
}

void Animation::update(float dt)
{
	static float previousTime = mCurrentTime;
	mCurrentTime += dt;
	float elapsedTime = mCurrentTime - previousTime;

	if(elapsedTime >= mInterval)
	{
		mCurrentFrameIndex++;
		mCurrentFrameIndex %= mFrames.size();
		previousTime = mCurrentTime;
	}
}

void Animation::draw()
{
	mFrames[mCurrentFrameIndex]->draw();
}
