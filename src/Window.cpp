#include "Window.h"

#include <iostream>

Window::Window(const std::string & title, int width, int height, bool fullscreen) :
	mTitle(title),
	mWidth(width),
	mHeight(height),
	mIsFullscreen(fullscreen)
{
}

Window::~Window()
{
	glfwDestroyWindow(mWindow);
}

bool Window::initialize()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	mWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr);
	if (mWindow == nullptr)
	{
		std::cerr << "failed to create window!" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(mWindow);

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

void Window::setTitle(const std::string & title)
{
	mTitle = title;

	glfwSetWindowTitle(mWindow, mTitle.c_str());
}

void Window::appendTitle(const std::string & str)
{
	std::string newTitle = mTitle + str;

	glfwSetWindowTitle(mWindow, newTitle.c_str());
}
