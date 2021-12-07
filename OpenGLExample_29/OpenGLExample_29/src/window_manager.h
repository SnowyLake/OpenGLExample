#pragma once
#include <map>
#include <string>
#include <optional>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "gl_camera.h"
#include "utility.hpp"
class WindowManager
{
public:
	WindowManager(const unsigned int& width, const unsigned int& height,const std::string& title, 
				  GLCamera* camera = nullptr, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
	~WindowManager();

	void SetCallback();
	void ProcessInput();
	void Show(std::optional<int> xPos = std::nullopt, 
			  std::optional<int> yPos = std::nullopt);
	void UpData();
	void Destory();
	//get
	GLFWwindow*	 Get()		 const;
	std::string	 GetTitle()  const;
	unsigned int GetWidth()	 const;
	unsigned int GetHeight() const;
private:
	GLFWwindow*	 m_window;
	GLCamera*	 m_camera;
	unsigned int m_width;
	unsigned int m_height;
	std::string	 m_title;

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
	static unsigned int CbID;	//静态ID，通过cbSID = cbID来访问指定对象非静态成员
	static std::map<unsigned int, WindowManager*> CbMap;	//静态对象映射表

	//call back pointer
	static WindowManager* CbPtr;
	//framebuffer size callback function
	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	//mouse callback function
	static void MouseCallback(GLFWwindow* window, double xPos, double yPos);
	//scroll callback function
	static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
};

