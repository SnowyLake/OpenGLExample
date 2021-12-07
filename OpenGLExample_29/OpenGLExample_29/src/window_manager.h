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
	//�����ڶ����ʵ������ʱ������cbPtr
	unsigned int m_cbID;			//������ID
	static unsigned int CbID;	//��̬ID��ͨ��cbSID = cbID������ָ������Ǿ�̬��Ա
	static std::map<unsigned int, WindowManager*> CbMap;	//��̬����ӳ���

	//call back pointer
	static WindowManager* CbPtr;
	//framebuffer size callback function
	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	//mouse callback function
	static void MouseCallback(GLFWwindow* window, double xPos, double yPos);
	//scroll callback function
	static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
};

