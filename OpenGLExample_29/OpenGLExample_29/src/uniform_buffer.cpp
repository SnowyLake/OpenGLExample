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

UniformBuffer& UniformBuffer::Bind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_UBO);
	return *this;
}

void UniformBuffer::UnBind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

UniformBuffer& UniformBuffer::BindPoint(GLuint index, GLintptr offset, GLsizeiptr size)
{
	if (offset == NULL && size == NULL)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, index, m_UBO);
	} else
	{
		glBindBufferRange(GL_UNIFORM_BUFFER, index, m_UBO, offset, size);
	}
	return *this;
}

UniformBuffer& UniformBuffer::SetSubData(GLintptr offset, GLsizeiptr size, const GLvoid* data)
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_UBO);
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	return *this;
}

//将shader的指定Uniform块绑定到某一绑定点上
void UniformBlockBindPoint(Shader shader, const char* blockName, unsigned int bindingPoint)
{
	glUniformBlockBinding(shader.GetID(),
						  glGetUniformBlockIndex(shader.GetID(), blockName),
						  bindingPoint);
}
