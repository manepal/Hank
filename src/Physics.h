#ifndef PHYSICS_H
#define PHYSICS_H


#include <Box2D\Box2D.h>

#include <Buzz\Transform.h>

class Box
{
public:
	Box();
	~Box();


	void init(b2World* world, const vec2& position, const vec2& dimensions);

	b2Body* getBody() { return mBody; }
	b2Fixture* getFixture() { return mFixture; }
	vec2& getDimensions() { return mDimensions; }

private:
	b2Body * mBody = nullptr;
	b2Fixture * mFixture = nullptr;
	vec2 mDimensions;
};


#endif // !PHYSICS_H