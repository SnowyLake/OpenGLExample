#pragma once
#include <tuple>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <gl_shader.h>

//将shader的指定Uniform块绑定到某一绑定点上
void UniformBlockBind(GLShader shader, const char* blockName, unsigned int bindingPoint)
{
	glUniformBlockBinding(shader.ID, glGetUniformBlockIndex(shader.ID, blockName), bindingPoint);
}

//获取指定窗口的帧缓冲尺寸
auto GetFramebufferSize(GLFWwindow* window)
{
	int _width, _height; 
	glfwGetFramebufferSize(window, &_width, &_height);
	return std::make_tuple(_width, _height);
}
