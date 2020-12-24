#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>
#include<iostream>

#include<GLCamera.h>

//camera
extern GLCamera camera;

class CreateWindow
{
public:
	GLFWwindow* window;

	CreateWindow(unsigned int width, unsigned int height, std::string title, GLFWmonitor* monitor, GLFWwindow* share, bool captureMouse);
	~CreateWindow();

	GLFWwindow* CreateMainWindow(GLFWmonitor* monitor, GLFWwindow* share, bool captureMouse);

	void SetCallback();
	void SetPerFrameTimeLogic();
	void ProcessInput();

	static unsigned int GetScrWidth();
	static unsigned int GetScrHeight();
	std::string GetWindowTitle();

private:
	static unsigned int scrWidth;
	static unsigned int scrHeight;
	std::string windowTitle;

	//camera
	static float lastX;
	static float lastY;
	static bool firstMouse;
	//timing
	float deltaTime;	// time between current frame and last frame
	float lastTime;

	void GLFWInit();

	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	static void MouseCallback(GLFWwindow* window, double xPos, double yPos);
	static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
};

