#pragma once
#include <vector>
#include <optional>
#include <tuple>
#include <string_view>
#include <format>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utility.hpp"

using uint = unsigned int;
using uchar = unsigned char;
enum class TextureType
{
	_2D = GL_TEXTURE_2D,
	_CUBE_MAP = GL_TEXTURE_CUBE_MAP
};
#define CAST_TO_GLTYPE(t) static_cast<uint>(t)
enum class MapType
{
	NONE,
	DIFFUSE,	//漫反射贴图
	SPECULAR,	//高光贴图
	NORMAL,		//法线贴图
	REFECTION,	//反射贴图
	EMISSION	//放射光贴图
};
template<TextureType Ty>
class Texture
{
public:
	//2d ctor
	Texture(const char* path, std::string_view name,
			int warpS = GL_CLAMP_TO_EDGE,
			int warpT = GL_CLAMP_TO_EDGE,
			int filterMax = GL_LINEAR,
			int filterMin = GL_LINEAR_MIPMAP_LINEAR);
	//cube map ctor
	Texture(const std::vector<const char*>& paths, std::string_view name,
			int warpS = GL_CLAMP_TO_EDGE,
			int warpT = GL_CLAMP_TO_EDGE,
			int warpR = GL_CLAMP_TO_EDGE,
			int filterMax = GL_LINEAR,
			int filterMin = GL_LINEAR);

	~Texture();
	Texture(const Texture&) = default;
	Texture(Texture&&) noexcept = default;
	Texture& operator=(const Texture&) = default;
	Texture& operator=(Texture&&) noexcept = default;

	//Gen texture
	void Generate(uchar* data, uint width, uint height,
				  uint nrChannels, MapType type);
	//Gen cubemap, std::tuple<data, width, height>
	void Generate(uchar* data, uint width, uint height, size_t i);
	void SetTexParameter();

	uint		 Get()	   const { return m_ID; }
	MapType		 GetType() const { return m_type; }
	std::string& GetName()		 { return m_name; }

	auto GetPath() const;

	//return std::tuple<m_width, m_height>
	std::tuple<uint, uint> GetSize(uint i = 0) const;
	int& GetWarpSMode() { return m_warpS; }
	int& GetWarpTMode() { return m_warpT; }
	//warning: 请检测返回值是否为std::nullopt
	std::optional<int>& GetWarpRMode() { return m_warpR; }

	int& GetFilterMinMode() { return m_filterMin; }
	int& GetFilterMaxMode() { return m_filterMax; }
private:
	const char* m_path;
	std::optional<std::vector<const char*>> m_paths;

	uint		m_ID;
	MapType		m_type;
	std::string m_name;
	
	std::optional<uint> m_width;
	std::optional<uint> m_height;
	std::optional<std::vector<uint>> m_cubeMapWidths;
	std::optional<std::vector<uint>> m_cubeMapHeights;

	int m_warpS;
	int m_warpT;
	std::optional<int> m_warpR;

	int m_format;
	int m_filterMax;
	int m_filterMin;
};

template<TextureType Ty>	/*2d ctor*/
inline Texture<Ty>::Texture(const char* path, std::string_view name,
							int warpS/* = GL_CLAMP_TO_EDGE */,
							int warpT/* = GL_CLAMP_TO_EDGE */,
							int filterMax/* = GL_LINEAR */,
							int filterMin/* = GL_LINEAR_MIPMAP_LINEAR */)
	:m_path(path),
	 m_paths(std::nullopt), 
	 m_type(MapType::NONE), 
	 m_name(name),
	 m_width(0), 
	 m_height(0), 
	 m_cubeMapWidths(std::nullopt), 
	 m_cubeMapHeights(std::nullopt),
	 m_warpS(warpS), 
	 m_warpT(warpT), 
	 m_warpR(std::nullopt),
	 m_format(GL_RGB),
	 m_filterMax(filterMax), 
	 m_filterMin(filterMin)
{
	glGenTextures(1, &m_ID);
}
template<TextureType Ty>
inline Texture<Ty>::Texture(const std::vector<const char*>& paths, std::string_view name,
							int warpS/* = GL_CLAMP_TO_EDGE */,
							int warpT/* = GL_CLAMP_TO_EDGE */,
							int warpR/* = GL_CLAMP_TO_EDGE */,
							int filterMax/* = GL_LINEAR */,
							int filterMin/* = GL_LINEAR */)
	:m_path(nullptr),
	 m_paths(paths),
	 m_type(MapType::NONE),
	 m_name(name),
	 m_width(std::nullopt),
	 m_height(std::nullopt),
	 m_cubeMapWidths(std::vector<uint>()),
	 m_cubeMapHeights(std::vector<uint>()),
	 m_warpS(warpS),
	 m_warpT(warpT),
	 m_warpR(warpR),
	 m_format(GL_RGB),
	 m_filterMax(filterMax),
	 m_filterMin(filterMin)
{
	glGenTextures(1, &m_ID);
}
template<TextureType Ty>
inline Texture<Ty>::~Texture()
{}

template<TextureType Ty>
inline auto Texture<Ty>::GetPath() const
{
	if constexpr (Ty == TextureType::_2D)
		return m_path;
	if constexpr (Ty == TextureType::_CUBE_MAP)
		return m_paths;
}

template<TextureType Ty>
inline std::tuple<uint, uint> Texture<Ty>::GetSize(uint i/* = 0*/) const
{
	if constexpr (Ty == TextureType::_2D)
	{
		return std::make_tuple(m_width, m_height);
	}
	if constexpr (Ty == TextureType::_CUBE_MAP)
	{
		return std::make_tuple(m_cubeMapWidths->at(i), m_cubeMapHeights->at(i));
	}
}

template<>
inline void Texture<TextureType::_2D>::Generate(uchar* data, uint width, uint height,
												uint nrChannels, MapType type)
{
	m_type	 = type;
	m_width	 = width;
	m_height = height;

	if (nrChannels == 1)
		m_format = GL_RED;
	else if (nrChannels == 3)
		m_format = GL_RGB;
	else if (nrChannels == 4)
		m_format = GL_RGBA;

	glBindTexture(CAST_TO_GLTYPE(TextureType::_2D), m_ID);
	glTexImage2D(CAST_TO_GLTYPE(TextureType::_2D), 0, m_format, *m_width, *m_height, 0, m_format, GL_UNSIGNED_BYTE, data);
}

template<>
inline void Texture<TextureType::_CUBE_MAP>::Generate(uchar* data, uint width, uint height, size_t i)
{
	glBindTexture(CAST_TO_GLTYPE(TextureType::_CUBE_MAP), m_ID);
	m_cubeMapWidths->emplace_back(width);
	m_cubeMapHeights->emplace_back(height);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, m_format, m_cubeMapWidths->at(i),
				 m_cubeMapHeights->at(i), 0, m_format, GL_UNSIGNED_BYTE, data);
}

template<TextureType Ty>
inline void Texture<Ty>::SetTexParameter()
{
	if constexpr (Ty == TextureType::_2D)
	{
		if (m_filterMin == GL_NEAREST_MIPMAP_NEAREST || m_filterMin == GL_LINEAR_MIPMAP_NEAREST ||
			m_filterMin == GL_NEAREST_MIPMAP_LINEAR  || m_filterMin == GL_LINEAR_MIPMAP_LINEAR)
		{
			glGenerateMipmap(CAST_TO_GLTYPE(Ty));
		}
		glTexParameteri(CAST_TO_GLTYPE(Ty), GL_TEXTURE_WRAP_S, m_warpS);
		glTexParameteri(CAST_TO_GLTYPE(Ty), GL_TEXTURE_WRAP_T, m_warpT);
		glTexParameteri(CAST_TO_GLTYPE(Ty), GL_TEXTURE_MIN_FILTER, m_filterMin);
		glTexParameteri(CAST_TO_GLTYPE(Ty), GL_TEXTURE_MAG_FILTER, m_filterMax);

		glBindTexture(CAST_TO_GLTYPE(Ty), 0);
	}
	if constexpr (Ty == TextureType::_CUBE_MAP)
	{
		glTexParameteri(CAST_TO_GLTYPE(Ty), GL_TEXTURE_WRAP_S, m_warpS);
		glTexParameteri(CAST_TO_GLTYPE(Ty), GL_TEXTURE_WRAP_T, m_warpT);
		glTexParameteri(CAST_TO_GLTYPE(Ty), GL_TEXTURE_WRAP_R, *m_warpR);
		glTexParameteri(CAST_TO_GLTYPE(Ty), GL_TEXTURE_MIN_FILTER, m_filterMin);
		glTexParameteri(CAST_TO_GLTYPE(Ty), GL_TEXTURE_MAG_FILTER, m_filterMax);

		glBindTexture(CAST_TO_GLTYPE(Ty), 0);
	}
}







