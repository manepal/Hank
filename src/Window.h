#ifndef WINDOW_H
#define WINDOW_H


#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <string>

class Window
{
public:
	 Window(const std::string&  title, int width, int height, bool fullscreen = false);
	~Window();


	bool initialize();
	void close();

	GLFWwindow* getWindowHandle() const;

	void setTitle(const std::string& title);
	// this appends the suppkied value to the current title
	void appendTitle(const std::string& str);

private:
	GLFWwindow * mWindow;

	std::string mTitle;
	int mWidth;
	int mHeight;
	bool mIsFullscreen;
};


#endif // WINDOW_H