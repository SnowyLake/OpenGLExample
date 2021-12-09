/*
* @Module Name: utility.hpp
* @Auther: SnowyLake
* @Version: 0.2
* -------------------------------------------------------
* @Abstract:
*	This is the utility tools hpp file.
*/
#pragma once
#include <tuple>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"


//将shader的指定Uniform块绑定到某一绑定点上
inline void UniformBlockBind(Shader shader, const char* blockName, unsigned int bindingPoint)
{
	glUniformBlockBinding(shader.GetID(), 
						  glGetUniformBlockIndex(shader.GetID(), blockName),
						  bindingPoint);
}

//获取指定窗口的帧缓冲尺寸
inline std::tuple<int, int> GetFramebufferSize(GLFWwindow* window)
{
	int _width, _height;
	glfwGetFramebufferSize(window, &_width, &_height);
	return std::make_tuple(_width, _height);
};

// TODO: File Name Info Process
class FileNameInfo
{
public:
	FileNameInfo(const std::string& file) :m_file(file)
	{
		auto size = m_file.size();

	}
	FileNameInfo(std::string_view file)
	{

	}
	FileNameInfo(const char* file)
	{

	}
	~FileNameInfo() = default;
	FileNameInfo(const FileNameInfo&) = default;
	FileNameInfo(FileNameInfo&&) = default;
	FileNameInfo& operator=(const FileNameInfo&) = default;
	FileNameInfo& operator=(FileNameInfo&&) = default;

	std::string GetFile() const { return m_file; }
	std::string GetFileName() const { return m_fileName; }
	std::string GetFilePath() const { return m_filePath; }
	std::string GetFileExtension() const { return m_fileExtension; }
private:
	std::string m_file;
	std::string m_fileName;
	std::string m_filePath;
	std::string m_fileExtension;
};