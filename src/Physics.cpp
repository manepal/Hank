#include "Physics.h"

Box::Box()
{
}

Box::~Box()
{
}

void Box::init(b2World * world, const vec2 & position, const vec2 & dimensions)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	mBody = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x / 2.0f, dimensions.y / 2.0f);;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	mFixture = mBody->CreateFixture(&fixtureDef);
}
