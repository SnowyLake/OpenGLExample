#include "../include/uniform_buffer_manager.h"

UniformBufferManager::UniformBufferManager(GLsizeiptr size, const GLvoid* data)
{
	glGenBuffers(1, &this->UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, this->UBO);
	glBufferData(GL_UNIFORM_BUFFER, size, data, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

UniformBufferManager::~UniformBufferManager()
{}

void UniformBufferManager::Bind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, this->UBO);
}

void UniformBufferManager::UnBind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBufferManager::SetSubData(GLintptr offset, GLsizeiptr size, const GLvoid* data)
{
	glBindBuffer(GL_UNIFORM_BUFFER, this->UBO);
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBufferManager::BindPoint(GLuint index, GLintptr offset, GLsizeiptr size)
{
	if (offset == NULL && size == NULL)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, index, this->UBO);
	} else
	{
		glBindBufferRange(GL_UNIFORM_BUFFER, index, this->UBO, offset, size);
	}
}
