#pragma once
#include <tuple>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

//��shader��ָ��Uniform��󶨵�ĳһ�󶨵���
inline void UniformBlockBind(Shader shader, const char* blockName, unsigned int bindingPoint)
{
	glUniformBlockBinding(shader.GetID(), glGetUniformBlockIndex(shader.GetID(), blockName), bindingPoint);
}

//��ȡָ�����ڵ�֡����ߴ�
inline std::tuple<int, int> GetFramebufferSize(GLFWwindow* window)
{
	int _width, _height;
	glfwGetFramebufferSize(window, &_width, &_height);
	return std::make_tuple(_width, _height);
}