#include "Dev_Map.h"

Dev_Map::Dev_Map(TexSPtr_t texture,
				 MapType type/* =  MapType::DIFFUSE*/,
				 uint warpS/* = GL_CLAMP_TO_EDGE */,
				 uint warpT/* = GL_CLAMP_TO_EDGE */,
				 uint filterMax/* = GL_LINEAR */,
				 uint filterMin/* = GL_LINEAR_MIPMAP_LINEAR */)
	:m_texture(texture),
	 m_type(type),
	 m_warpS(warpS),
	 m_warpT(warpT),
	 m_filterMax(filterMax),
	 m_filterMin(filterMin)
{
	if (m_texture->GetNrChannels() == 1)
		m_internalFormat = m_imageFormat = GL_RED;
	else if (m_texture->GetNrChannels() == 3)
		m_internalFormat = m_imageFormat = GL_RGB;
	else if (m_texture->GetNrChannels() == 4)
		m_internalFormat = m_imageFormat = GL_RGBA;

	Generate();
}

Dev_Map::Dev_Map(const Dev_Map& map)
{
	m_type = map.m_type;
	m_texture = map.m_texture;
	m_warpS = map.m_warpS;
	m_warpT = map.m_warpT;
	m_filterMax = map.m_filterMax;
	m_filterMin = map.m_filterMin;
	m_internalFormat = map.m_internalFormat;
	m_imageFormat = map.m_imageFormat;

	//重新生成ID
	m_ID = 0;
	Generate();
}

Dev_Map::Dev_Map(Dev_Map&& map) noexcept
{
	m_ID = map.m_ID;
	m_type = map.m_type;
	m_texture = map.m_texture;
	m_warpS = map.m_warpS;
	m_warpT = map.m_warpT;
	m_filterMax = map.m_filterMax;
	m_filterMin = map.m_filterMin;
	m_internalFormat = map.m_internalFormat;
	m_imageFormat = map.m_imageFormat;
}

Dev_Map& Dev_Map::operator=(const Dev_Map& map)
{
	m_type = map.m_type;
	m_texture = map.m_texture;
	m_warpS = map.m_warpS;
	m_warpT = map.m_warpT;
	m_filterMax = map.m_filterMax;
	m_filterMin = map.m_filterMin;
	m_internalFormat = map.m_internalFormat;
	m_imageFormat = map.m_imageFormat;

	//重新生成ID
	m_ID = 0;
	Generate();
	return*this;
}

Dev_Map& Dev_Map::operator=(Dev_Map&& map) noexcept
{
	m_ID = map.m_ID;
	m_type = map.m_type;
	m_texture = map.m_texture;
	m_warpS = map.m_warpS;
	m_warpT = map.m_warpT;
	m_filterMax = map.m_filterMax;
	m_filterMin = map.m_filterMin;
	m_internalFormat = map.m_internalFormat;
	m_imageFormat = map.m_imageFormat;
	return *this;
}

void Dev_Map::Generate()
{
	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);
	glTexImage2D(GL_TEXTURE_2D, 
				 0,
				 m_internalFormat, 
				 m_texture->GetWidth(), 
				 m_texture->GetHeight(),
				 0, 
				 m_imageFormat, 
				 GL_UNSIGNED_BYTE, 
				 m_texture->GetData());

	if (m_filterMin == GL_NEAREST_MIPMAP_NEAREST || m_filterMin == GL_LINEAR_MIPMAP_NEAREST ||
		m_filterMin == GL_NEAREST_MIPMAP_LINEAR  || m_filterMin == GL_LINEAR_MIPMAP_LINEAR)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_warpS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_warpT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMax);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMin);
}
