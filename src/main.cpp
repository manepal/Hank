#include "Application.h"

#include <Buzz\Engine.h>

#include <memory>

int main()
{
	BUZZ::Engine* engine = BUZZ::Engine::getInstance();
	Application app;

	if (!engine->startup(&app))
	{
		engine->shutdown();
		getchar();
		return -1;
	}

	engine->run();

	return 0;
}
