#ifndef ANIMATION_CONTROLLER_H
#define ANIMAITON_CONTROLLER_H


#include <map>
#include <memory>
#include <string>

#include "Animation.h"

class AnimationController
{
public:
	AnimationController();
	~AnimationController();

	void addAnimation(const std::string& name, std::shared_ptr<Animation> animation);
	void setActiveAnimation(const std::string& name);

	void update(float dt);
	void draw();

private:
	std::string mActiveAnimationName;
	bool mIsAnimationChanged;
	std::shared_ptr<Animation> mActiveAnimation;

	std::map<std::string, std::shared_ptr<Animation>> mAnimations;
};


#endif // ANIMATION_CONTROLLER_H