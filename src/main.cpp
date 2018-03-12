#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>


#include <iostream>


GLFWwindow* gWindow;
const char* APP_TITLE = "Hank";
const int WIDTH = 1280;
const int HEIGHT = 768;

bool init();
void mainLoop();
void cleanup();

int main()
{
	if (!init())
	{
		cleanup();
		return -1;
	}
	
	mainLoop();
	cleanup();

	return 0;
}

bool init()
{
	if (!glfwInit())
	{
		std::cerr << "failed to initialize GLFW!" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	gWindow = glfwCreateWindow(WIDTH, HEIGHT, APP_TITLE, nullptr, nullptr);
	if (gWindow == nullptr)
	{
		std::cerr << "failed to create window!" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(gWindow);

	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		std::cerr << "failed to initialize GLEW!" << std::endl;
		return false;
	}

	return true;
}

void mainLoop()
{
	while (!glfwWindowShouldClose(gWindow))
	{
		glfwPollEvents();
		glfwSwapBuffers(gWindow);
	}
}

void cleanup()
{
	if (gWindow != nullptr)
	{
		glfwDestroyWindow(gWindow);
	}

	glfwTerminate();
}