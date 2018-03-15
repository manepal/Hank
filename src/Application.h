#ifndef APPLICATION_H
#define APPLICATION_H


#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <string>

#include "Camera.h"
#include "ShaderProgram.h"

class Application
{
public:
	 Application(const std::string& appTitle, int windowWidth, int windowHeight);
	~Application();

	void run();

private:
	int mWindowWidth;
	int mWindowHeight;
	std::string mAppTitle;

	GLFWwindow* mWindow;

	ShaderProgram mShaderProgram;
	Camera mCamera;

	bool initialize();
	void mainLoop();
	void cleanup();

	void loadResources();
	void update(float dt);
	void draw();
};


#endif // APPLICATION_H