#include "uniform_buffer_manager.h"

UniformBufferManager::UniformBufferManager(GLsizeiptr size, const GLvoid* data)
{
	glGenBuffers(1, &m_UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, m_UBO);
	glBufferData(GL_UNIFORM_BUFFER, size, data, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

UniformBufferManager::~UniformBufferManager()
{}

void UniformBufferManager::Bind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_UBO);
}

void UniformBufferManager::UnBind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBufferManager::SetSubData(GLintptr offset, GLsizeiptr size, const GLvoid* data)
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_UBO);
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBufferManager::BindPoint(GLuint index, GLintptr offset, GLsizeiptr size)
{
	if (offset == NULL && size == NULL)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, index, m_UBO);
	} else
	{
		glBindBufferRange(GL_UNIFORM_BUFFER, index, m_UBO, offset, size);
	}
}
