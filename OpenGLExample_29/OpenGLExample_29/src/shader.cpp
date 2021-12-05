#include "shader.h"

Shader::Shader(std::string_view name)
	:m_name(name), m_ID(0)
{}

void Shader::Compile(const char* vShaderCode, const char* fShaderCode, const char* gShaderCode)
{
	unsigned int vShader, fShader, gShader;
	//vertex shader
	vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vShaderCode, nullptr);
	glCompileShader(vShader);
	CheckCompileErrors(vShader, "VERTEX");
	//fragment shader
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fShaderCode, nullptr);
	glCompileShader(fShader);
	CheckCompileErrors(fShader, "FRAGMENT");
	//if geometry shader is given, compile geometry shader
	if (gShaderCode != nullptr)
	{
		gShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gShader, 1, &gShaderCode, nullptr);
		glCompileShader(gShader);
		CheckCompileErrors(gShader, "GEOMETRY");
	}
	//shader program
	m_ID = glCreateProgram();
	glAttachShader(m_ID, vShader);
	glAttachShader(m_ID, fShader);
	if (gShaderCode != nullptr)
		glAttachShader(m_ID, gShader);
	glLinkProgram(m_ID);
	CheckCompileErrors(m_ID, "PROGRAM");

	glDeleteShader(vShader);
	glDeleteShader(fShader);
	if (gShaderCode != nullptr)
	{
		glDeleteShader(gShader);
	}
}

uint Shader::GetID() const
{
	return m_ID;
}

std::string& Shader::GetName()
{
	return m_name;
}

Shader& Shader::Use()
{
	glUseProgram(m_ID);
	return *this;
}

Shader& Shader::SetInt(const char* name, int value)
{
	glUniform1i(glGetUniformLocation(m_ID, name), value);
	return *this;
}

Shader& Shader::SetBool(const char* name, bool value)
{
	glUniform1i(glGetUniformLocation(m_ID, name), static_cast<int>(value));
	return *this;
}

Shader& Shader::SetFloat(const char* name, float value)
{
	glUniform1f(glGetUniformLocation(m_ID, name), value);
	return *this;
}

Shader& Shader::SetVec2(const char* name, float x, float y)
{
	glUniform2f(glGetUniformLocation(m_ID, name), x, y);
	return *this;
}

Shader& Shader::SetVec2(const char* name, const glm::vec2& value)
{
	glUniform2fv(glGetUniformLocation(m_ID, name), 1, glm::value_ptr(value));
	return *this;
}

Shader& Shader::SetVec3(const char* name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(m_ID, name), x, y, z);
	return *this;
}

Shader& Shader::SetVec3(const char* name, const glm::vec3& value)
{
	glUniform3fv(glGetUniformLocation(m_ID, name), 1, glm::value_ptr(value));
	return *this;
}

Shader& Shader::SetVec4(const char* name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(m_ID, name), x, y, z, w);
	return *this;
}

Shader& Shader::SetVec4(const char* name, const glm::vec4& value)
{
	glUniform4fv(glGetUniformLocation(m_ID, name), 1, glm::value_ptr(value));
	return *this;
}

Shader& Shader::SetMat2(const char* name, const glm::mat2& value)
{
	glUniformMatrix2fv(glGetUniformLocation(m_ID, name), 1, GL_FALSE, glm::value_ptr(value));
	return *this;
}

Shader& Shader::SetMat3(const char* name, const glm::mat3& value)
{
	glUniformMatrix3fv(glGetUniformLocation(m_ID, name), 1, GL_FALSE, glm::value_ptr(value));
	return *this;
}

Shader& Shader::SetMat4(const char* name, const glm::mat4& value)
{
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, GL_FALSE, glm::value_ptr(value));
	return *this;
}

void Shader::CheckCompileErrors(uint shader, std::string_view type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);

#if _MSVC_LANG >= 202002L	/*CXX20*/
			std::cout << std::format("ERROR::SHADER::COMPILATION_ERROR of type:{}"
									 "\n{}"
									 "\n-- -------------------------------------------------- --", type, infoLog);
#else	
			std::cout << "ERROR::SHADER::COMPILATION_ERROR of type:"<< type 
				<< "\n" << infoLog 
				<< "\n -- --------------------------------------------------- -- " << std::endl;
#endif
		}
	}
	else
	{
		glGetShaderiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);

#if _MSVC_LANG >= 202002L	/*CXX20*/
			std::cout << std::format("ERROR::PROGRAM:LINKING_ERROR of type:{}"
									 "\n{}"
									 "\n-- -------------------------------------------------- --", type, infoLog);
#else	
			std::cout << "ERROR::PROGRAM:LINKING_ERROR of type:" << type 
				<< "\n" << infoLog
				<< "\n -- --------------------------------------------------- -- " << std::endl;
#endif
		}
	}
}
