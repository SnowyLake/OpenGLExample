#include "Dev_Texture.h"

Dev_Texture::Dev_Texture(const FileNameInfo& info)
	:m_width(0), m_height(0), m_nrChannels(0), m_data(nullptr),
	 m_info(info)
{}

Dev_Texture::~Dev_Texture()
{}

void Dev_Texture::SetParameter(uint width, uint height, uint nrChannels, uchar* data)
{
	m_width = width;
	m_height = height;
	m_nrChannels = nrChannels;
	m_data = std::move(std::unique_ptr<uchar>(data));

	//uint dataSize = GetUCharSize(data);
	//m_data = new uchar[dataSize + 1];
	//memcpy(m_data, data, dataSize + 1);
	////test
	//assert(m_data == data);
}

//Dev_Texture::Dev_Texture(const Dev_Texture& tex)
//	:m_width(tex.GetWidth()),
//	 m_height(tex.GetHeight()),
//	 m_nrChannels(tex.GetNrChannels()),
//	 m_info(tex.GetInfo())
//{
//	uint dataSize = GetUCharSize(tex.GetData());
//	m_data = new uchar[dataSize + 1];
//	memcpy(m_data, tex.GetData(), dataSize + 1);
//
//	//test
//	assert(m_data == tex.GetData());
//}
//
//Dev_Texture::Dev_Texture(Dev_Texture&& tex) noexcept
//	:m_width(tex.GetWidth()),
//	 m_height(tex.GetHeight()),
//	 m_nrChannels(tex.GetNrChannels()),
//	 m_data(tex.GetData()),
//	 m_info(tex.GetInfo())
//{
//	tex.SetData(nullptr);
//}
//
//Dev_Texture& Dev_Texture::operator=(const Dev_Texture& tex)
//{
//	if (this == &tex)	//检测自我赋值(self assignment)
//		return *this;
//
//	m_width = tex.GetWidth();
//	m_height = tex.GetHeight();
//	m_nrChannels = tex.GetNrChannels();
//	m_info = tex.GetInfo();
//
//	delete m_data;
//	uint dataSize = GetUCharSize(tex.GetData());
//	m_data = new uchar[dataSize + 1];
//	memcpy(m_data, tex.GetData(), dataSize + 1);
//
//	//test
//	assert(m_data == tex.GetData());
//
//	return *this;
//}
//
//Dev_Texture& Dev_Texture::operator=(Dev_Texture&& tex) noexcept
//{
//	if (this == &tex)	//检测自我赋值(self assignment)
//		return *this;
//
//	
//	m_width = tex.GetWidth();
//	m_height = tex.GetHeight();
//	m_nrChannels = tex.GetNrChannels();
//	delete m_data;
//	m_data = tex.GetData();
//	m_info = tex.GetInfo();
//
//	tex.SetData(nullptr);
//
//	return *this;
//}

