#ifndef APPLICATION_H
#define APPLICATION_H


#include <string>

#include <Buzz\Camera.h>
#include <Buzz\ShaderProgram.h>
#include <Buzz\Window.h>
#include <Buzz\IApplication.h>


class Application : public BUZZ::IApplication
{
public:
	 Application();

	// Inherited via IApplication
	virtual void startup() override;
	virtual void update(float dt) override;
	virtual void draw() override;
	virtual void shutdown() override;

private:
};

#endif // APPLICATION_H