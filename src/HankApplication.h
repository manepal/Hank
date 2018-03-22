#ifndef HANK_APPLICATION_H
#define HANK_APPLICATION_H


#include <string>

#include <Buzz\IApplication.h>

#include "Player.h"

class HankApplication : public BUZZ::IApplication
{
public:
	HankApplication();

	// Inherited via IApplication
	virtual void startup() override;
	virtual void update(float dt) override;
	virtual void render() override;
	virtual void shutdown() override;

private:
	Player * mHank;
};


#endif // !HANK_APPLICAITON_H