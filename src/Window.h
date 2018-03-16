#ifndef WINDOW_H
#define WINDOW_H


#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <string>


// singleton window class
class Window
{
public:
	// returns singleton instance of window
	static Window* getInstance();

	bool initialize(const std::string&  title, int width, int height, bool fullscreen = false);
	void close();

	GLFWwindow* getWindowHandle() const;
	int getWidth() const;
	int getHeight() const;

	void setTitle(const std::string& title);
	void setWindowSize(int width, int height);
	// this appends the suppkied value to the current title
	void appendTitle(const std::string& str);

private:
	Window();
	~Window();

private:
	GLFWwindow * mWindow;

	std::string mTitle;
	int mWidth;
	int mHeight;
	bool mIsFullscreen;

	void setWindowCallbacks();

	// glfw window callbacks
	static void glfw_OnKey(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void glfw_OnMouseMove(GLFWwindow* window, double posX, double posY);
	static void glfw_OnMouseScroll(GLFWwindow* window, double deltaX, double deltaY);
	static void glfw_OnFrameBufferSize(GLFWwindow* window, int width, int height);
};


#endif // WINDOW_H