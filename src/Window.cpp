#include "Window.h"

#include <iostream>


Window::Window()
{}

Window::~Window()
{
	glfwDestroyWindow(mWindow);
}

Window * Window::getInstance()
{
	static Window* mInstance = new Window();

	return mInstance;
}

bool Window::initialize(const std::string&  title, int width, int height, bool fullscreen)
{
	mTitle = title;
	mWidth = width;
	mHeight = height;
	mIsFullscreen = fullscreen;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWmonitor* monitor = nullptr;

	if (mIsFullscreen)
	{
		monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* vMode = glfwGetVideoMode(monitor);

		mWidth = vMode->width;
		mHeight = vMode->height;
	}
	// create window
	mWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), monitor, nullptr);
	if (mWindow == nullptr)
	{
		std::cerr << "failed to create window!" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(mWindow);

	setWindowCallbacks();

	glViewport(0, 0, mWidth, mHeight);

	return true;
}


void Window::close()
{
	glfwSetWindowShouldClose(mWindow, GL_TRUE);
}

GLFWwindow * Window::getWindowHandle() const
{
	return mWindow;
}

int Window::getWidth() const
{
	return mWidth;
}

int Window::getHeight() const
{
	return mHeight;
}

void Window::setTitle(const std::string & title)
{
	mTitle = title;

	glfwSetWindowTitle(mWindow, mTitle.c_str());
}

void Window::setWindowSize(int width, int height)
{
	mWidth = width;
	mHeight = height;
}

void Window::appendTitle(const std::string & str)
{
	std::string newTitle = mTitle + str;

	glfwSetWindowTitle(mWindow, newTitle.c_str());
}

void Window::setWindowCallbacks()
{
	glfwSetKeyCallback(mWindow, glfw_OnKey);
	glfwSetCursorPosCallback(mWindow, glfw_OnMouseMove);
	glfwSetScrollCallback(mWindow, glfw_OnMouseScroll);
	glfwSetWindowSizeCallback(mWindow, glfw_OnFrameBufferSize);
}

void Window::glfw_OnKey(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void Window::glfw_OnMouseMove(GLFWwindow * window, double posX, double posY)
{

	//std::cout << "on mouse move." << std::endl;
}

void Window::glfw_OnMouseScroll(GLFWwindow * window, double deltaX, double deltaY)
{

	//std::cout << "on mouse scroll." << std::endl;
}

void Window::glfw_OnFrameBufferSize(GLFWwindow * window, int width, int height)
{
	Window::getInstance()->setWindowSize(width, height);;

	glViewport(0, 0, width, height);
}