#ifndef ANIMATION_H
#define ANIMATION_H


#include <vector>
#include <memory>

#include "Sprite.h"

class Animation
{
public:
	Animation(float interval);
	~Animation();

	void addFrame(const std::string& texturePath);
	// set interval in seconds
	void setInterval(float interval);

	void reset();
	void update(float dt);
	void draw();

private:
	float mInterval;
	int mCurrentFrameIndex;

	std::vector<std::shared_ptr<Sprite>> mFrames;
};


#endif // ANIMATION_H