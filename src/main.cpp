#include "HankApplication.h"
#include "PrototypeApplication.h"

#include <Buzz\Engine.h>

#include <memory>

int main()
{
	BUZZ::Engine* engine = BUZZ::Engine::getInstance();
	HankApplication hankApp;
	PrototypeApplication prototype;

	if (!engine->startup(&hankApp))
	{
		engine->shutdown();
		getchar();
		return -1;
	}

	engine->run();

	return 0;
}
