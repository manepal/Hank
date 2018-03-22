#include "Player.h"

#include <memory>

#include <Buzz\Animation.h>
#include <Buzz\Input.h>

const float VELOCITY = 150.0f;

Player::Player()
{
	mPosition.x = 0.0f;
	mPosition.y = 0.0f;

	mRotation = 0.0f;

	mScale.x = 1.0f;
	mScale.y = 1.0f;
}

Player::Player(const vec2 & position, float rotation, const vec2 & scale)
{
	mPosition.x = position.x;
	mPosition.y = position.y;

	mRotation = rotation;

	mScale.x = scale.x;
	mScale.y = scale.y;
}

void Player::update(float dt)
{
	if (BUZZ::Input::getKeyDown(KEY_RIGHT))
	{
		mAnimController.setActiveAnimation("walk");
		mScale.x = abs(mScale.x);
		mPosition.x += VELOCITY * dt;
	}
	else if (BUZZ::Input::getKeyDown(KEY_LEFT))
	{

		mAnimController.setActiveAnimation("walk");
		if (mScale.x > 0.0f)
		{
			mScale.x *= -1.0f;
		}
		mPosition.x -= VELOCITY * dt;
	}
	else
	{
		mAnimController.setActiveAnimation("idle");

	}

	if (BUZZ::Input::getKeyDown(KEY_UP))
	{

		mAnimController.setActiveAnimation("jump");
	}
	else if (BUZZ::Input::getKeyDown(KEY_DOWN))
	{

		mAnimController.setActiveAnimation("duck");
	}

	mAnimController.update(dt);
}

void Player::draw()
{
	mAnimController.draw();
}

void Player::loadResources()
{
	std::shared_ptr<BUZZ::Animation> idle(new BUZZ::Animation(1.0f));
	std::shared_ptr<BUZZ::Animation> walk(new BUZZ::Animation(0.075f));
	std::shared_ptr<BUZZ::Animation> duck(new BUZZ::Animation(10.0f));
	std::shared_ptr<BUZZ::Animation> jump(new BUZZ::Animation(10.0f));
	
	// add frames to idle animation
	idle->addFrame("textures/Player/Idle/p1_front.png");
	idle->addFrame("textures/player/Idle/p1_stand.png");

	// add frames to duck animation
	duck->addFrame("textures/Player/Duck/p1_duck.png");

	// add frames to jump animation
	jump->addFrame("textures/Player/Jump/p1_jump.png");

	// add frames to walk animation
	for (int i = 0; i < 11; i++)
	{
		std::string imagePath = "textures/Player/Walk/p1_walk" + std::to_string(i) + ".png";
		walk->addFrame(imagePath);
	}

	mAnimController.addAnimation("idle", idle);
	mAnimController.addAnimation("walk", walk);
	mAnimController.addAnimation("duck", duck);
	mAnimController.addAnimation("jump", jump);
}

const vec2 & Player::getPosition() const
{
	return mPosition;
}

const float Player::getRotation() const
{
	return mRotation;
}

const vec2 & Player::getScale() const
{
	return mScale;
}

const mat4 & Player::getModelMatrix() const
{
	mat4 t = translate(mat4(), vec3(mPosition.x, mPosition.y, 0.0f));
	mat4 r = rotate(mat4(), radians(mRotation), vec3(0.0f, 0.0f, 1.0f));
	mat4 s = scale(mat4(), vec3(mScale.x, mScale.y, 1.0f));

	return (t * r * s);
}
