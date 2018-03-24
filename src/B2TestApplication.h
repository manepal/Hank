#ifndef B2_TEST_APPLICATION
#define	B2_TEST_APPLICATION


#include <Buzz\IApplication.h>
#include <Buzz\Sprite.h>

#include <Box2D\Box2D.h>
#include <vector>
#include <memory>

#include "Player.h"
#include "Physics.h"

class B2TestApplication : public BUZZ::IApplication
{
public:
	B2TestApplication();

	// Inherited via IApplication
	virtual void startup() override;
	virtual void update(float dt) override;
	virtual void render() override;
	virtual void shutdown() override;

private:
	Player m_player;

	BUZZ::Sprite m_playerSprite;
	BUZZ::ShaderProgram m_colorShaderProgram;
	BUZZ::ShaderProgram m_textureShaderProgram;

	// box 2d stuff
	std::unique_ptr<b2World> m_world;
	b2Body* m_groundBody;
	b2Body* m_playerRigidBody;

	int m_velocityIterations;
	int m_positionIterations;

	std::vector<Box> m_boxes;
};


#endif // !B2_TEST_APPLICATION