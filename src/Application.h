#ifndef APPLICATION_H
#define APPLICATION_H


#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <string>

#include <Buzz\Camera.h>
#include <Buzz\ShaderProgram.h>
#include <Buzz\Window.h>

class Application
{
public:
	 Application(const std::string& appTitle, int windowWidth, int windowHeight, bool fullscreen = false);
	~Application();

	void run();

private:
	int mWindowWidth;
	int mWindowHeight;
	std::string mAppTitle; 
	bool mIsFullscreen;

	BUZZ::ShaderProgram mShaderProgram;
	BUZZ::Camera mCamera;

	float mFPS;
	float mFrameTime;

	bool initialize();
	void mainLoop();
	void cleanup();

	void loadResources();
	void update(double dt);
	void draw();
	void showFPS();
};


#endif // APPLICATION_H