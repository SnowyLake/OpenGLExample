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
	unsigned int ID;
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
		this->ID = glCreateProgram();
		glAttachShader(this->ID, vertexShader);
		glAttachShader(this->ID, fragmentShader);
		if (geometryPath != nullptr)
			glAttachShader(this->ID, geometryShader);
		glLinkProgram(this->ID);
		CheckCompileErrors(this->ID, "PROGRAM");

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		if (geometryPath != nullptr)
			glDeleteShader(geometryShader);
	}
	//activate the shader
	GLShader& Use()
	{
		glUseProgram(this->ID);
		return *this;
	}
	//utility uniform functions
	GLShader& SetBool(const std::string& name, bool value)
	{
		glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
		return *this;
	}
	// ------------------------------------------------------------------------
	GLShader& SetInt(const std::string& name, int value)
	{
		glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
		return *this;
	}
	// ------------------------------------------------------------------------
	GLShader& SetFloat(const std::string& name, float value)
	{
		glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
		return *this;
	}
	// ------------------------------------------------------------------------
	GLShader& SetVec2(const std::string& name, const glm::vec2& value)
	{
		glUniform2fv(glGetUniformLocation(this->ID, name.c_str()), 1, &value[0]);
		return *this;
	}
	GLShader& SetVec2(const std::string& name, float x, float y)
	{
		glUniform2f(glGetUniformLocation(this->ID, name.c_str()), x, y);
		return *this;
	}
	// ------------------------------------------------------------------------
	GLShader& SetVec3(const std::string& name, const glm::vec3& value)
	{
		glUniform3fv(glGetUniformLocation(this->ID, name.c_str()), 1, &value[0]);
		return *this;
	}
	GLShader& SetVec3(const std::string& name, float x, float y, float z)
	{
		glUniform3f(glGetUniformLocation(this->ID, name.c_str()), x, y, z);
		return *this;
	}
	// ------------------------------------------------------------------------
	GLShader& SetVec4(const std::string& name, const glm::vec4& value)
	{
		glUniform4fv(glGetUniformLocation(this->ID, name.c_str()), 1, &value[0]);
		return *this;
	}
	GLShader& SetVec4(const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(this->ID, name.c_str()), x, y, z, w);
		return *this;
	}
	// ------------------------------------------------------------------------
	GLShader& SetMat2(const std::string& name, const glm::mat2& mat)
	{
		glUniformMatrix2fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		return *this;
	}
	// ------------------------------------------------------------------------
	GLShader& SetMat3(const std::string& name, const glm::mat3& mat)
	{
		glUniformMatrix3fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		return *this;
	}
	// ------------------------------------------------------------------------
	GLShader& SetMat4(const std::string& name, const glm::mat4& mat)
	{
		glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		return *this;
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
				std::cout << "ERROR::SHADER::COMPILATION_ERROR of type:"
					<< type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetShaderiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM:LINKING_ERROR of type:" 
					<< type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};