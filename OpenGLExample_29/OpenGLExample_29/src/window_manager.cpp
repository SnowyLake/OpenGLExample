#include "window_manager.h"

//static
unsigned int WindowManager::sm_cbID = 0;
std::map<unsigned int, WindowManager*> WindowManager::sm_cbMap;
WindowManager* WindowManager::sm_cbPtr = nullptr;
//---------------------------------------------------------------
//public
//---------------------------------------------------------------

//init
WindowManager::WindowManager(GLCamera* camera,
							 const unsigned int& width, const unsigned int& height,
							 const std::string& title, GLFWmonitor* monitor, GLFWwindow* share)
	:m_camera(camera), m_scrWidth(width), m_scrHeight(height), m_windowTitle(title), m_lastX(static_cast<float>(width) / 2.0f), 
	 m_lastY(static_cast<float>(height) / 2.0f), m_firstMouse(true), m_isMouseDragging(false), m_deltaTime(0.0f), m_lastTime(0.0f)
{
	m_window = CreateWindow(monitor, share);

	if (sm_cbMap.empty())
		m_cbID = 1;
	else
		m_cbID = sm_cbMap.size() + 1;
	sm_cbMap.emplace(m_cbID, this);
}
WindowManager::~WindowManager() { }

void WindowManager::SetCallback()
{
	WindowManager::sm_cbID = m_cbID;
	glfwSetFramebufferSizeCallback(m_window, FrameBufferSizeCallback);
	glfwSetCursorPosCallback(m_window, MouseCallback);
	glfwSetScrollCallback(m_window, ScrollCallback);
}

void WindowManager::ProcessInput()
{
	if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		m_isMouseDragging = true;
	}	
	else
	{
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		m_isMouseDragging = false;
	}
		
	SetPerFrameTimeLogic();
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);
	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		m_camera->ProcessKeyboard(CM::FORWARD, m_deltaTime);
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		m_camera->ProcessKeyboard(CM::BACKWARD, m_deltaTime);
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		m_camera->ProcessKeyboard(CM::LEFT, m_deltaTime);
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		m_camera->ProcessKeyboard(CM::RIGHT, m_deltaTime);
	if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
		m_camera->ProcessKeyboard(CM::RISE, m_deltaTime);
	if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		m_camera->ProcessKeyboard(CM::FALL, m_deltaTime);
}

void WindowManager::Show()
{
	glfwShowWindow(m_window);
}

void WindowManager::UpData()
{
	auto [width, height] = GetFramebufferSize(m_window);
	m_scrWidth = width;
	m_scrHeight = height;
	glfwSwapBuffers(m_window);
	glfwPollEvents();
	
}

void WindowManager::Delete()
{
	glfwTerminate();
}

GLFWwindow*		WindowManager::GetWindow()		const { return m_window; }
unsigned int	WindowManager::GetScrWidth()	const { return m_scrWidth; }
unsigned int	WindowManager::GetScrHeight()	const { return m_scrHeight; }
std::string		WindowManager::GetWindowTitle() const { return m_windowTitle; }

//---------------------------------------------------------------
//private
//---------------------------------------------------------------

//init glfw
void WindowManager::GLFWInit()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
#ifdef _APPLE_
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // _APPLE_
}

//create window
GLFWwindow* WindowManager::CreateWindow(GLFWmonitor* monitor, GLFWwindow* share)
{
	GLFWInit();
	GLFWwindow* window = glfwCreateWindow(m_scrWidth, m_scrHeight, m_windowTitle.c_str(), monitor, share);
	if(window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);

	//glad
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return nullptr;
	}
	return window;
}

void WindowManager::SetPerFrameTimeLogic()
{
	float currentFrame = glfwGetTime();
	m_deltaTime = currentFrame - m_lastTime;
	m_lastTime = currentFrame;
}

//framebuffer size callback function
void WindowManager::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	if (sm_cbMap.empty())
		return;
	sm_cbPtr = sm_cbMap.at(sm_cbID);

	glViewport(0, 0, width, height);
}

//mouse callback function
void WindowManager::MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (sm_cbMap.empty())
		return;
	sm_cbPtr = sm_cbMap.at(sm_cbID);

	if (sm_cbPtr->m_firstMouse)
	{
		sm_cbPtr->m_lastX = xPos;
		sm_cbPtr->m_lastY = yPos;
		sm_cbPtr->m_firstMouse = false;
	}
	float xOffset = xPos - (sm_cbPtr->m_lastX);
	float yOffset = (sm_cbPtr->m_lastY) - yPos;
	sm_cbPtr->m_lastX = xPos;
	sm_cbPtr->m_lastY = yPos;

	if (sm_cbPtr->m_isMouseDragging)
	{
		sm_cbPtr->m_camera->ProcessMouseMovement(xOffset, yOffset);
	}
		
}

//scroll callback function
void WindowManager::ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	if (sm_cbMap.empty())
		return;
	sm_cbPtr = sm_cbMap.at(sm_cbID);

	sm_cbPtr->m_camera->ProcessMouseScroll(yOffset);
}
