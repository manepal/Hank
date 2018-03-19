#include "Animation.h"

#include <GLFW\glfw3.h>

Animation::Animation(float interval) :
	mInterval(interval),
	mCurrentFrameIndex(0)
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

void Animation::reset()
{
	mCurrentFrameIndex = 0;
}

void Animation::update(float dt)
{
	static float duration = 0.0f;

	duration += dt;

	if(duration >= mInterval)
	{
		mCurrentFrameIndex++;
		mCurrentFrameIndex %= mFrames.size();
		duration = 0.0f;
	}
}

void Animation::draw()
{
	mFrames[mCurrentFrameIndex]->draw();
}
