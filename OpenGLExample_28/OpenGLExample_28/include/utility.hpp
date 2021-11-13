#pragma once
#include <tuple>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <gl_shader.h>

//��shader��ָ��Uniform��󶨵�ĳһ�󶨵���
void UniformBlockBind(GLShader shader, const char* blockName, unsigned int bindingPoint)
{
	glUniformBlockBinding(shader.ID, glGetUniformBlockIndex(shader.ID, blockName), bindingPoint);
}

//��ȡָ�����ڵ�֡����ߴ�
auto GetFramebufferSize(GLFWwindow* window)
{
	int _width, _height; 
	glfwGetFramebufferSize(window, &_width, &_height);
	return std::make_tuple(_width, _height);
}
