#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<GLCamera.h>

#include<iostream>

void ProcessInput(GLFWwindow* window);
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);

//setting
extern const unsigned int SCR_WIDTH;
extern const unsigned int SCR_HEIGHT;

//camera
extern GLCamera camera;

//timing
extern float deltaTime;		// time between current frame and last frame
extern float lastTime;

//extern GLFWwindow* window;
GLFWwindow* CreateWindow(unsigned int width, unsigned int height, const char* Title);





