#include "AnimationController.h"

#include <iostream>

AnimationController::AnimationController() :
	mIsAnimationChanged(false)
{
}

AnimationController::~AnimationController()
{
	mAnimations.clear();
}

void AnimationController::addAnimation(const std::string& name, std::shared_ptr<Animation> animation)
{
	mActiveAnimation = animation;

	mAnimations.insert(std::pair<std::string, std::shared_ptr<Animation>>(name, animation));
}

void AnimationController::setActiveAnimation(const std::string & name)
{
	if (mActiveAnimationName == name) return;

	mActiveAnimationName = name;
	mIsAnimationChanged = true;
}

void AnimationController::update(float dt)
{
	if (mAnimations.empty()) return;

	if (mIsAnimationChanged)
	{
		auto iterator = mAnimations.find(mActiveAnimationName);
		if (iterator == mAnimations.end())	// not found
		{
			std::cerr << "animation '" << mActiveAnimationName << "' does not exist." << std::endl;
		}
		else
		{
			mActiveAnimation = iterator->second;
			mActiveAnimation->reset();
		}

		mIsAnimationChanged = false;
	}

	mActiveAnimation->update(dt);
}

void AnimationController::draw()
{
	if (mAnimations.empty()) return;

	mActiveAnimation->draw();
}
