#include "HankApplication.h"
#include "B2TestApplication.h"

#include <Buzz\Engine.h>

#include <memory>

int main()
{
	BUZZ::Engine* engine = BUZZ::Engine::getInstance();
	HankApplication hankApp;
	B2TestApplication b2App;

	if (!engine->startup(&b2App))
	{
		engine->shutdown();
		getchar();
		return -1;
	}

	engine->run();

	return 0;
}
