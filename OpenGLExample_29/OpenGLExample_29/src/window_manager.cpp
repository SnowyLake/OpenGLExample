#include "window_manager.h"
//static
unsigned int WindowManager::CbID = 0;
std::map<unsigned int, WindowManager*> WindowManager::CbMap;
WindowManager* WindowManager::CbPtr = nullptr;
//---------------------------------------------------------------
//public
//---------------------------------------------------------------

//init
WindowManager::WindowManager(const unsigned int& width, const unsigned int& height,const std::string& title,
							 GLCamera* camera, GLFWmonitor* monitor, GLFWwindow* share)
	:m_width(width), m_height(height), m_title(title), m_camera(camera), m_lastX(static_cast<float>(width) / 2.0f),
	 m_lastY(static_cast<float>(height) / 2.0f), m_firstMouse(true), m_isMouseDragging(false), m_deltaTime(0.0f), m_lastTime(0.0f)
{
	m_window = CreateWindow(monitor, share);

	if (CbMap.empty())
		m_cbID = 1;
	else
		m_cbID = CbMap.size() + 1;
	CbMap.emplace(m_cbID, this);
}
WindowManager::~WindowManager() { }

void WindowManager::SetCallback()
{
	WindowManager::CbID = m_cbID;
	glfwSetFramebufferSizeCallback(m_window, FrameBufferSizeCallback);
	if (m_camera != nullptr)
	{
		glfwSetCursorPosCallback(m_window, MouseCallback);
		glfwSetScrollCallback(m_window, ScrollCallback);
	}
}

void WindowManager::ProcessInput()
{
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);
	if (m_camera != nullptr)
	{
		if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			m_isMouseDragging = true;
		} else
		{
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			m_isMouseDragging = false;
		}
		SetPerFrameTimeLogic();
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
}

void WindowManager::Show(std::optional<int> xPos/* = std::nullopt*/,
						 std::optional<int> yPos/* = std::nullopt*/)
{
	if (xPos.has_value() && yPos.has_value())
		glfwSetWindowPos(m_window, *xPos, *yPos);
	glfwShowWindow(m_window);
}

void WindowManager::UpData()
{
	auto [width, height] = GetFramebufferSize(m_window);
	m_width = width;
	m_height = height;
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void WindowManager::Destory()
{
	glfwTerminate();
}

GLFWwindow*	 WindowManager::Get()		const { return m_window; }
std::string	 WindowManager::GetTitle()  const { return m_title;  }
std::tuple<uint, uint> WindowManager::GetSize() const
{
	return std::make_tuple(m_width, m_height);
}


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
	GLFWwindow* window = glfwCreateWindow(m_width, m_height, m_title.c_str(), monitor, share);
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
	if (CbMap.empty())
		return;
	CbPtr = CbMap.at(CbID);

	glViewport(0, 0, width, height);
}

//mouse callback function
void WindowManager::MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (CbMap.empty())
		return;
	CbPtr = CbMap.at(CbID);

	if (CbPtr->m_firstMouse)
	{
		CbPtr->m_lastX = xPos;
		CbPtr->m_lastY = yPos;
		CbPtr->m_firstMouse = false;
	}
	float xOffset = xPos - (CbPtr->m_lastX);
	float yOffset = (CbPtr->m_lastY) - yPos;
	CbPtr->m_lastX = xPos;
	CbPtr->m_lastY = yPos;

	if (CbPtr->m_isMouseDragging)
	{
		CbPtr->m_camera->ProcessMouseMovement(xOffset, yOffset);
	}
		
}

//scroll callback function
void WindowManager::ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	if (CbMap.empty())
		return;
	CbPtr = CbMap.at(CbID);

	CbPtr->m_camera->ProcessMouseScroll(yOffset);
}
