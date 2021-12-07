#include "uniform_buffer.h"

UniformBuffer::UniformBuffer(GLsizeiptr size, const GLvoid* data)
{
	glGenBuffers(1, &m_UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, m_UBO);
	glBufferData(GL_UNIFORM_BUFFER, size, data, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

UniformBuffer::~UniformBuffer()
{}

void UniformBuffer::Bind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_UBO);
}

void UniformBuffer::UnBind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::SetSubData(GLintptr offset, GLsizeiptr size, const GLvoid* data)
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_UBO);
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::BindPoint(GLuint index, GLintptr offset, GLsizeiptr size)
{
	if (offset == NULL && size == NULL)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, index, m_UBO);
	} else
	{
		glBindBufferRange(GL_UNIFORM_BUFFER, index, m_UBO, offset, size);
	}
}
