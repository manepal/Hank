#ifndef PLAYER_H
#define PLAYER_H


#include <Buzz\Transform.h>
#include <Buzz\AnimationController.h>
#include <Buzz\Sprite.h>


class Player
{
public:
	Player();
	Player(const vec2& position, float rotation, const vec2& scale);

	void update(float dt);
	void draw();

	void loadResources();

	const vec2& getPosition() const;;
	const float getRotation() const;
	const vec2& getScale() const;

	const mat4& getModelMatrix() const;

	void setPosition(const vec2& pos)
	{
		mPosition.x = pos.x;
		mPosition.y = pos.y;
	}

private:
	vec2 mPosition;
	float mRotation;
	vec2 mScale;
	int mWidth;
	int mHeight;

	BUZZ::Sprite mSprite;

	BUZZ::AnimationController mAnimController;
};


#endif // !PLAYER_H