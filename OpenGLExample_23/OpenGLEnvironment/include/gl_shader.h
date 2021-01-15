#pragma once
#include<glad/glad.h>
#include<glm/glm.hpp>

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

class GLShader
{
public:
	unsigned int shaderProgram;
	GLShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
	{
		//1.retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::string geometryCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		std::ifstream gShaderFile;
		//ensure ifstream objects can throw exceptions
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			//open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			//read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			//close file handlers
			vShaderFile.close();
			fShaderFile.close();
			//convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
			// if geometry shader path is present, also load a geometry shader
			if (geometryPath != nullptr)
			{
				gShaderFile.open(geometryPath);
				std::stringstream gShaderStream;
				gShaderStream << gShaderFile.rdbuf();
				gShaderFile.close();
				geometryCode = gShaderStream.str();
			}
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		//2.compile shaders
		unsigned int vertexShader, fragmentShader;
		//vertex shader
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vShaderCode, NULL);
		glCompileShader(vertexShader);
		CheckCompileErrors(vertexShader, "VERTEX");
		//fragment shader
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
		glCompileShader(fragmentShader);
		CheckCompileErrors(fragmentShader, "FRAGMENT");
		// if geometry shader is given, compile geometry shader
		unsigned int geometryShader;
		if (geometryPath != nullptr)
		{
			const char* gShaderCode = geometryCode.c_str();
			geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometryShader, 1, &gShaderCode, NULL);
			glCompileShader(geometryShader);
			CheckCompileErrors(geometryShader, "GEOMETRY");
		}
		//shader program
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		if (geometryPath != nullptr)
			glAttachShader(shaderProgram, geometryShader);
		glLinkProgram(shaderProgram);
		CheckCompileErrors(shaderProgram, "PROGRAM");

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		if (geometryPath != nullptr)
			glDeleteShader(geometryShader);
	}
	//activate the shader
	void use()
	{
		glUseProgram(shaderProgram);
	}
	//utility uniform functions
	void SetBool(const std::string& name, bool value)const
	{
		glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void SetInt(const std::string& name, int value)const
	{
		glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void SetFloat(const std::string& name, float value)const
	{
		glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void SetVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
	}
	void SetVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), x, y);
	}
	// ------------------------------------------------------------------------
	void SetVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
	}
	void SetVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z);
	}
	// ------------------------------------------------------------------------
	void SetVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
	}
	void SetVec4(const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z, w);
	}
	// ------------------------------------------------------------------------
	void SetMat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void SetMat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void SetMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
private:
	//check for shader compilation/linking errors
	void CheckCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER::COMPILATION_ERROR of type:" << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetShaderiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM:LINKING_ERROR of type:" << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};