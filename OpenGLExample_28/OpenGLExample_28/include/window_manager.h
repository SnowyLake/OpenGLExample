#pragma once
#include<string>
#include<iostream>

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include <gl_camera.h>

//camera
extern GLCamera camera;

class WindowManager
{
public:
	GLFWwindow* window;

	WindowManager(const unsigned int& width, const unsigned int& height, 
				  const std::string& title, GLFWmonitor* monitor, GLFWwindow* share, const bool captureMouse);
	~WindowManager();

	void SetCallback();
	void ProcessInput();
	void Show(unsigned int xPos, unsigned int yPos);

	unsigned int GetScrWidth();
	unsigned int GetScrHeight();
	std::string GetWindowTitle();

private:
	//GLCamera* cam;
	unsigned int scrWidth;
	unsigned int scrHeight;
	std::string windowTitle;

	//camera
	static float lastX;
	static float lastY;
	static bool firstMouse;
	//timing
	float deltaTime;	// time between current frame and last frame
	float lastTime;

	void GLFWInit();
	GLFWwindow* CreateWindow(GLFWmonitor* monitor, GLFWwindow* share, bool captureMouse);
	void SetPerFrameTimeLogic();

	//framebuffer size callback function
	static WindowManager* FBSCb;
	void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	static void FrameBufferSizeCallbackFunc(GLFWwindow* window, int width, int height);

	//mouse callback function
	static WindowManager* MCb;
	void MouseCallback(GLFWwindow* window, double xPos, double yPos);
	static void MouseCallbackFunc(GLFWwindow* window, double xPos, double yPos);

	//scroll callback function
	static WindowManager* SCb;
	void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	static void ScrollCallbackFunc(GLFWwindow* window, double xOffset, double yOffset);
};

