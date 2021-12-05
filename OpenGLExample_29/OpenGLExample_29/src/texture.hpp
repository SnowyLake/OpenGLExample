#pragma once
#include <vector>
#include <optional>
#include <tuple>
#include <string_view>
#include <format>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
using uint = unsigned int;
using uchar = unsigned char;
enum class TextureType
{
	_2D,
	_CUBE_MAP
};
enum class MapType
{
	NONE,
	DIFFUSE,	//¬˛∑¥…‰Ã˘Õº
	SPECULAR,	//∏ﬂπ‚Ã˘Õº
	NORMAL,		//∑®œﬂÃ˘Õº
	REFECTION,	//∑¥…‰Ã˘Õº
	EMISSION	//∑≈…‰π‚Ã˘Õº
};
template<TextureType Ty>
class Texture
{
public:

	Texture(std::string_view name);
	~Texture();
	Texture(const Texture&) = default;
	Texture(Texture&&) noexcept = default;
	Texture& operator=(const Texture&) = default;
	Texture& operator=(Texture&&) noexcept = default;

	//Gen texture
	void Generate(uchar* data, uint width, uint height,
				  uint nrChannels, MapType type);
	//Gen cubemap, std::tuple<data, width, height>
	void Generate(std::vector<std::tuple<uchar*, int, int>> dataSet);

	inline uint Get() const { return m_ID; }
	inline std::string& GetName() { return m_name; }
	inline MapType		GetType() const { return m_type; }

	//return std::tuple<m_width, m_height>
	inline std::tuple<uint, uint> GetSize() const { return std::make_tuple(m_width, m_height); }

	inline uint& GetWarpSMode() { return m_warpS; }
	inline uint& GetWarpTMode() { return m_warpT; }
	inline uint& GetWarpRMode() { return m_warpR; }
	inline uint& GetFilterMinMode() { return m_filterMin; }
	inline uint& GetFilterMaxMode() { return m_filterMax; }
private:
	std::string m_name;
	MapType		m_type;
	uint m_ID;
	uint m_width, m_height;
	std::optional<std::vector<uint>> m_cubeMapWidths, m_cubeMapHeights;
	uint m_format;
	uint m_warpS;
	uint m_warpT;
	uint m_warpR;
	uint m_filterMin;
	uint m_filterMax;
};

template<TextureType Ty>
inline Texture<Ty>::Texture(std::string_view name)
	:m_name(name), m_width(0), m_height(0), m_format(GL_RGB),
	 m_warpS(GL_CLAMP_TO_EDGE), m_warpT(GL_CLAMP_TO_EDGE), m_filterMax(GL_LINEAR)
{
	glGenTextures(1, &m_ID);
	if (Ty == TextureType::_CUBE_MAP)
	{
		m_type = MapType::NONE;
		m_warpR = GL_CLAMP_TO_EDGE;
		m_filterMin = GL_LINEAR;
	} else {
		m_warpR = 0;
		m_filterMin = GL_LINEAR_MIPMAP_LINEAR;
		m_cubeMapWidths  = std::nullopt;
		m_cubeMapHeights = std::nullopt;
	}
}
template<TextureType Ty>
inline Texture<Ty>::~Texture()
{}

template<>
inline void Texture<TextureType::_2D>::Generate(uchar* data, uint width, uint height,
								  uint nrChannels, MapType type)
{
	m_width = width;
	m_height = height;

	if (nrChannels == 1)
		m_format = GL_RED;
	else if (nrChannels == 3)
		m_format = GL_RGB;
	else if (nrChannels == 4)
		m_format = GL_RGBA;

	glBindTexture(GL_TEXTURE_2D, m_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, data);

	if (m_filterMin == GL_NEAREST_MIPMAP_NEAREST || m_filterMin == GL_LINEAR_MIPMAP_NEAREST ||
		m_filterMin == GL_NEAREST_MIPMAP_LINEAR || m_filterMin == GL_LINEAR_MIPMAP_LINEAR)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_warpS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_warpT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMax);

	glBindTexture(GL_TEXTURE_2D, 0);
}

template<>
inline void Texture<TextureType::_CUBE_MAP>::Generate(std::vector<std::tuple<uchar*, int, int>> dataSet)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID);
	for (size_t i = 0; i < dataSet.size(); i++)
	{
		m_cubeMapWidths->at(i)  = std::get<1>(dataSet[i]);
		m_cubeMapHeights->at(i) = std::get<2>(dataSet[i]);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, m_format, m_cubeMapWidths->at(i), 
					 m_cubeMapHeights->at(i), 0, m_format, GL_UNSIGNED_BYTE, std::get<0>(dataSet[i]));

	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, m_warpS);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, m_warpT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, m_warpR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, m_filterMin);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, m_filterMax);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}





