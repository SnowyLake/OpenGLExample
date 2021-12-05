#pragma once
#include <map>
#include <string>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "gl_camera.h"
#include "utility.hpp"
class WindowManager
{
public:
	WindowManager(GLCamera* camera, 
				  const unsigned int& width, const unsigned int& height,
				  const std::string& title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
	~WindowManager();

	void SetCallback();
	void ProcessInput();
	void Show();
	void UpData();
	void Delete();
	//get
	GLFWwindow*	 GetWindow()	  const;
	unsigned int GetScrWidth()	  const;
	unsigned int GetScrHeight()	  const;
	std::string	 GetWindowTitle() const;
private:
	GLFWwindow*	 m_window;
	GLCamera*	 m_camera;
	unsigned int m_scrWidth;
	unsigned int m_scrHeight;
	std::string	 m_windowTitle;

	//camera
	float m_lastX;
	float m_lastY;
	bool  m_firstMouse;
	bool  m_isMouseDragging;

	//timing
	float m_deltaTime;	//time between current frame and last frame
	float m_lastTime;

	void GLFWInit();
	GLFWwindow* CreateWindow(GLFWmonitor* monitor, GLFWwindow* share);
	void SetPerFrameTimeLogic();

	//callback func
	//-------------
	//当存在多个类实例对象时，管理cbPtr
	unsigned int m_cbID;			//本对象ID
	static unsigned int sm_cbID;	//静态ID，通过cbSID = cbID来访问指定对象非静态成员
	static std::map<unsigned int, WindowManager*> sm_cbMap;	//静态对象映射表

	//call back pointer
	static WindowManager* sm_cbPtr;
	//framebuffer size callback function
	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	//mouse callback function
	static void MouseCallback(GLFWwindow* window, double xPos, double yPos);
	//scroll callback function
	static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
};

