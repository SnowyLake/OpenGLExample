#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class UniformBufferManager
{
public:
	UniformBufferManager(GLsizeiptr size, const GLvoid* data = nullptr);
	~UniformBufferManager();

	void Bind();
	void UnBind();

	void SetSubData(GLintptr offset, GLsizeiptr size, const GLvoid* data);
	void BindPoint(GLuint index, GLintptr offset = NULL, GLsizeiptr size = NULL);

private:
	unsigned int UBO;
};

