#pragma once
#include <tuple>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

//将shader的指定Uniform块绑定到某一绑定点上
inline void UniformBlockBind(Shader shader, const char* blockName, unsigned int bindingPoint)
{
	glUniformBlockBinding(shader.GetID(), glGetUniformBlockIndex(shader.GetID(), blockName), bindingPoint);
}

//获取指定窗口的帧缓冲尺寸
inline std::tuple<int, int> GetFramebufferSize(GLFWwindow* window)
{
	int _width, _height;
	glfwGetFramebufferSize(window, &_width, &_height);
	return std::make_tuple(_width, _height);
}