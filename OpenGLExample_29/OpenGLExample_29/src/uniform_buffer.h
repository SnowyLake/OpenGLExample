#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

class UniformBuffer
{
public:
	UniformBuffer(GLsizeiptr size, const GLvoid* data = nullptr);
	~UniformBuffer();

	UniformBuffer& Bind();
	void UnBind();

	UniformBuffer& BindPoint(GLuint index, GLintptr offset = NULL, GLsizeiptr size = NULL);
	UniformBuffer& SetSubData(GLintptr offset, GLsizeiptr size, const GLvoid* data);

private:
	unsigned int m_UBO;
};

//将shader的指定Uniform块绑定到某一绑定点上
void UniformBlockBindPoint(Shader shader, const char* blockName, unsigned int bindingPoint);



