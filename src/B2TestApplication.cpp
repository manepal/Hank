#include "B2TestApplication.h"

#include <Buzz\Transform.h>

B2TestApplication::B2TestApplication()
{
	mAppTitle = "Box2D Test Application";
	mWindowWidth = 1366;
	mWindowHeight = 768;
	mIsFullscreen = false;
}

void B2TestApplication::startup()
{
	// load graphics
	m_player.loadResources();
	m_player.setPosition(vec2(0.0f, 300.0f));

	m_playerSprite = BUZZ::Sprite(255, 0, 0, 255);
	m_playerSprite.load();
	
	m_colorShaderProgram.loadShaders("shaders/color_shader.vert.glsl", "shaders/color_shader.frag.glsl");

	b2Vec2 gravity(0.0f, -10.0f);
	m_world = std::make_unique<b2World>(gravity);

	// ground rigid body
	b2BodyDef  groundBodyDef;
	groundBodyDef.position.Set(0.0f, -9.8f);
	m_groundBody = m_world->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	m_groundBody->CreateFixture(&groundBox, 0.0f);

	Box newBox;
	newBox.init(m_world.get(), vec2(0.0f, 14.0f), vec2(15.0f, 15.0f));
	m_boxes.push_back(newBox);

	m_velocityIterations = 6;
	m_positionIterations = 2;
}

void B2TestApplication::update(float dt)
{
	/*mWorld->Step(dt, mVelocityIterations, mPositionIterations);
	b2Vec2 position = mPlayerRigidBody->GetPosition();
	mPlayer.setPosition(vec2(position.x, position.y));
	float32 angle = mPlayerRigidBody->GetAngle();

	printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);*/

	m_player.update(dt);
}

void B2TestApplication::render()
{
	mat4 model;
	mat4 view;
	mat4 projection;

	model = m_player.getModelMatrix();
	view = mCamera.getViewMatrix();
	projection = mCamera.getOrtho();

	m_colorShaderProgram.use();
	m_colorShaderProgram.setUniform("model", model);
	m_colorShaderProgram.setUniform("view", view);
	m_colorShaderProgram.setUniform("projection", projection);

	for (auto box : m_boxes)
	{
		m_playerSprite.draw();
	}

	//mPlayer.draw();
	mShaderProgram.unUse();
}

void B2TestApplication::shutdown()
{
}
