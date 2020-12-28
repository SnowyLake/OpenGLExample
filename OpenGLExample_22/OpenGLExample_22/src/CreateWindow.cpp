#include "..\include\CreateWindow.h"

//camera
GLCamera camera(glm::vec3(0.0f, -8.0f, 20.0f));
//static
float CreateWindow::lastX;
float CreateWindow::lastY;
bool CreateWindow::firstMouse;

//-----------------------public-------------------------
//init
CreateWindow::CreateWindow(unsigned int width, unsigned int height, std::string title, GLFWmonitor* monitor, GLFWwindow* share, bool captureMouse)
{
	this->scrWidth = width;
	this->scrHeight = height;
	this->windowTitle = title;
	//camera
	this->lastX = width / 2.0f;
	this->lastY = height / 2.0f;
	this->firstMouse = true;
	//timing
	this->deltaTime = 0.0f;		// time between current frame and last frame
	this->lastTime = 0.0f;

	this->window = CreateMainWindow(monitor, share, captureMouse);

	//std::cout << "init" << std::endl;
}
CreateWindow::~CreateWindow() 
{
	std::cout << "Class:CreateWindow Destructor Called." << std::endl;
}

//create window
GLFWwindow* CreateWindow::CreateMainWindow(GLFWmonitor* monitor, GLFWwindow* share, bool captureMouse)
{
	GLFWInit();
	GLFWwindow* window = glfwCreateWindow(scrWidth, scrHeight, windowTitle.c_str(), monitor, share);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);

	//tell GLFW to capture our mouse
	if (captureMouse == true)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return nullptr;
	}
	//std::cout << "create window" << std::endl;
	return window;
}

void CreateWindow::SetCallback()
{
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallbackFunc);
	glfwSetCursorPosCallback(window, MouseCallbackFunc);
	glfwSetScrollCallback(window, ScrollCallbackFunc);
}
void CreateWindow::SetPerFrameTimeLogic()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastTime;
	lastTime = currentFrame;
}
void CreateWindow::ProcessInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.ProcessKeyboard(RISE, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_CAPS_LOCK) == GLFW_PRESS)
		camera.ProcessKeyboard(FALL, deltaTime);

	//std::cout << "proc input" << std::endl;
}

unsigned int CreateWindow::GetScrWidth() { return scrWidth; }
unsigned int CreateWindow::GetScrHeight() { return scrHeight; }
std::string CreateWindow::GetWindowTitle() { return windowTitle; }

//-------------------------private-----------------------------
//init glfw
void CreateWindow::GLFWInit()
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

//framebuffer size callback function
CreateWindow* CreateWindow::FBSCb = nullptr;
void CreateWindow::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void CreateWindow::FrameBufferSizeCallbackFunc(GLFWwindow* window, int width, int height)
{
	FBSCb->FrameBufferSizeCallback(window, width, height);
}

//mouse callback function
CreateWindow* CreateWindow::MCb = nullptr;
void CreateWindow::MouseCallback(GLFWwindow* window, double xPos, double yPos)
{

	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	float xoffset = xPos - lastX;
	float yoffset = lastY - yPos;
	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
void CreateWindow::MouseCallbackFunc(GLFWwindow* window, double xPos, double yPos)
{
	MCb->MouseCallback(window, xPos, yPos);
}


//scroll callback function
CreateWindow* CreateWindow::SCb = nullptr;
void CreateWindow::ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	camera.ProcessMouseScroll(yOffset);
}
void CreateWindow::ScrollCallbackFunc(GLFWwindow* window, double xOffset, double yOffset)
{
	SCb->ScrollCallback(window, xOffset, yOffset);
}
