#pragma once
#include "texture.hpp"
#include "Dev_Texture.h"
using TexSPtr_t = std::shared_ptr<Dev_Texture>;
class Dev_Map
{
public:
	explicit Dev_Map(TexSPtr_t texture,
					 MapType type = MapType::DIFFUSE,
					 uint warpS = GL_CLAMP_TO_EDGE,
					 uint warpT = GL_CLAMP_TO_EDGE,
					 uint filterMax = GL_LINEAR,
					 uint filterMin = GL_LINEAR_MIPMAP_LINEAR);
	~Dev_Map() = default;
	Dev_Map(const Dev_Map&);
	Dev_Map(Dev_Map&&) noexcept;
	Dev_Map& operator=(const Dev_Map&);
	Dev_Map& operator=(Dev_Map&&) noexcept;

	void Generate();

	//字段访问，不可修改
	uint		 GetID()		 const { return m_ID;	}
	MapType		 GetType()		 const { return m_type; }
	Dev_Texture* GetTexture()	 const { return m_texture.get(); }

	uint	GetWarpS()			 const { return m_warpS; }
	uint	GetWarpT()			 const { return m_warpT; }
	uint	GetFilterMax()		 const { return m_filterMax; }
	uint	GetFilterMin()		 const { return m_filterMin; }
	uint	GetInternalFormat()	 const { return m_internalFormat; }
	GLenum	GetImageFormat()	 const { return m_imageFormat; }
	//字段访问，可修改参数
	void	SetWarpS(uint val)		
	{ m_warpS = val; glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_warpS); }
	void	SetWarpT(uint val)			 
	{ m_warpT = val; glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_warpT); }
	void	SetFilterMax(uint val)		 
	{ m_filterMax = val; glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMax); }
	void	SetFilterMin(uint val)		 
	{ m_filterMin = val; glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMin); }

private:
	//不可修改字段
	uint	  m_ID;
	MapType	  m_type;
	TexSPtr_t m_texture;
	//可修改字段
	uint	m_warpS;
	uint	m_warpT;
	uint	m_filterMax;
	uint	m_filterMin;
	//不可修改字段
	uint	m_internalFormat;	//format of texture object
	GLenum	m_imageFormat;		//format of loaded image
};

