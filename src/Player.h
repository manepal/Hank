#ifndef PLAYER_H
#define PLAYER_H


#include <Buzz\Transform.h>
#include <Buzz\AnimationController.h>

class Player
{
public:
	Player();
	Player(const vec2& position, float rotation, const vec2& scale);

	void update(float dt);
	void draw();

	void loadResources();

	const vec2& getPosition() const;
	const float getRotation() const;
	const vec2& getScale() const;

	const mat4& getModelMatrix() const;

private:
	vec2 mPosition;
	float mRotation;
	vec2 mScale;

	BUZZ::AnimationController mAnimController;
};


#endif // !PLAYER_H