#pragma once
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utility.hpp"

using uint = GLuint;
using uchar = unsigned char;
class Dev_Texture
{
public:
	Dev_Texture(const FileNameInfo& info);
	~Dev_Texture();
	Dev_Texture(const Dev_Texture&) = delete;
	Dev_Texture(Dev_Texture&&) noexcept = delete;
	Dev_Texture& operator=(const Dev_Texture&) = delete;
	Dev_Texture& operator=(Dev_Texture&&) noexcept = delete;

	void SetParameter(uint width, uint height, uint nrChannels, uchar* data);
	void SetData(uchar* data) { m_data.reset(data); }

	//字段访问，不可修改
	uint			GetWidth()		const { return m_width; }
	uint			GetHeight()		const { return m_height; }
	uint			GetNrChannels()	const { return m_nrChannels; }
	uchar*			GetData()		const { return m_data.get(); }
	FileNameInfo	GetInfo()		const { return m_info; }
private:
	uint	m_width;
	uint	m_height;
	uint	m_nrChannels;
	std::unique_ptr<uchar> m_data;
	FileNameInfo m_info;
};



