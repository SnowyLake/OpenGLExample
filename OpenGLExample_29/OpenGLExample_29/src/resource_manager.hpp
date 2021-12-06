#pragma once
#include <map>
#include <vector>
#include <tuple>
#include <optional>
#include <string>
#include <string_view>

#include <stb_image.h>

#include "texture.hpp"
#include "shader.h"

class ResourceMananger
{
public:
	static ResourceMananger& GetInstance();

	//shader
	Shader& LoadShader(const char* vPath, const char* fPath, const char* gPath = nullptr,
						 std::optional<std::string_view> name = std::nullopt);
	Shader& GetShader(const std::string& shaderName);
	uint GetShaderCount() const;
	//texture
	Texture<TextureType::_2D>&
	LoadTexture(const char* path, MapType type,
				std::optional<std::string_view> name = std::nullopt);
	Texture<TextureType::_CUBE_MAP>&
	LoadTexture(const std::vector<const char*>& paths,
				std::optional<std::string_view> name = std::nullopt);

	template<TextureType Ty>
	Texture<Ty>& GetTexture(const std::string& texName);
	template<TextureType Ty>
	uint GetTextureCount() const;
	
private:
	ResourceMananger();
	~ResourceMananger() = default;
	ResourceMananger(const ResourceMananger&) = delete;
	ResourceMananger(ResourceMananger&&) = delete;
	ResourceMananger& operator=(const ResourceMananger&) = delete;
	ResourceMananger& operator=(ResourceMananger&&) = delete;

	//对象保存
	std::map<std::string, Shader> m_shaders;
	std::map<std::string, Texture<TextureType::_2D>> m_textures_2d;
	std::map<std::string, Texture<TextureType::_CUBE_MAP>> m_textures_cube_map;
	//实际总数
	uint m_shaderCount;
	uint m_tex2DCount;
	uint m_texCubeMapCount;
	//默认命名编号
	uint m_shaderNameCount;
	uint m_tex2DNameCount;
	uint m_texCubeMapNameCount;

	Shader LoadShaderFromFile(const char* vPath, const char* fPath, const char* gPath, std::string_view name);

	Texture<TextureType::_2D>
	LoadTextureFromFile(const char* path, MapType type, std::string_view name);
	Texture<TextureType::_CUBE_MAP>
	LoadTextureFromFile(const std::vector<const char*>& paths, std::string_view name);
};

inline ResourceMananger& ResourceMananger::GetInstance()
{
	static ResourceMananger instance;
	return instance;
}
inline ResourceMananger::ResourceMananger()
	:m_shaderCount(0), m_tex2DCount(0), m_texCubeMapCount(0),
	m_shaderNameCount(0), m_tex2DNameCount(0), m_texCubeMapNameCount(0)
{}

//shader
//------------------------
inline Shader& ResourceMananger::GetShader(const std::string& shaderName)
{
	return m_shaders.at(shaderName);
}
inline uint ResourceMananger::GetShaderCount() const
{
	return m_shaderCount;
}
inline Shader& ResourceMananger::LoadShader(const char* vPath, const char* fPath, const char* gPath,
											std::optional<std::string_view> name /*= std::nullopt*/)
{
	//TODO: 需要检测是否与已有对象重名
	Shader shader = LoadShaderFromFile(vPath, fPath, gPath, name.value_or
	(
									   std::format("shader_{}", ++m_shaderNameCount)
	));
	m_shaders.emplace(shader.GetName(), shader);
	return m_shaders.at(shader.GetName());
}

inline Shader ResourceMananger::LoadShaderFromFile(const char* vPath, const char* fPath, const char* gPath,
												   std::string_view name)
{
	//retrieve the vertex/fragment source code from filePath
	std::string vShaderCodeStr;
	std::string fShaderCodeStr;
	std::string gShaderCodeStr;

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
		vShaderFile.open(vPath);
		fShaderFile.open(fPath);
		std::stringstream vShaderStream, fShaderStream;
		//read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//close file handlers
		vShaderFile.close();
		fShaderFile.close();
		//convert stream into string
		vShaderCodeStr = vShaderStream.str();
		fShaderCodeStr = fShaderStream.str();
		//if geometry shader path is present, also load a geometry shader
		if (gPath != nullptr)
		{
			gShaderFile.open(gPath);
			std::stringstream gShaderStream;
			gShaderStream << gShaderFile.rdbuf();
			gShaderFile.close();
			gShaderCodeStr = gShaderStream.str();
		}
	} catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCodeChar = vShaderCodeStr.c_str();
	const char* fShaderCodeChar = fShaderCodeStr.c_str();
	const char* gShaderCodeChar = gPath != nullptr ? gShaderCodeStr.c_str() : nullptr;
	Shader shader(name);
	shader.Compile(vShaderCodeChar, fShaderCodeChar, gShaderCodeChar);
	return shader;
}


//texture
//-------------------------
template<TextureType Ty>
inline Texture<Ty>& ResourceMananger::GetTexture(const std::string& texName)
{
	if constexpr (Ty == TextureType::_2D)
		return m_textures_2d.at(texName);
	if constexpr (Ty == TextureType::_CUBE_MAP)
		return m_textures_cube_map.at(texName);
}
template<TextureType Ty>
inline uint ResourceMananger::GetTextureCount() const
{
	if constexpr (Ty == TextureType::_2D)
		return m_tex2DCount;
	if constexpr (Ty == TextureType::_CUBE_MAP)
		return m_texCubeMapCount;
}

inline Texture<TextureType::_2D>&
ResourceMananger::LoadTexture(const char* path, MapType type,
							  std::optional<std::string_view> name /*= std::nullopt*/)
{
	//TODO: 需要检测是否与已有对象重名
	auto tex = LoadTextureFromFile(path, type, name.value_or
	(
								   std::format("texture_{}", ++m_tex2DNameCount)
	));
	m_textures_2d.emplace(tex.GetName(), tex);
	m_tex2DCount++;
	return m_textures_2d.at(tex.GetName());
}
inline Texture<TextureType::_CUBE_MAP>&
ResourceMananger::LoadTexture(const std::vector<const char*>& paths,
							  std::optional<std::string_view> name /*= std::nullopt*/)
{
	//TODO: 需要检测是否与已有对象重名
	auto tex = LoadTextureFromFile(paths, name.value_or
	(
								   std::format("texture_{}", ++m_texCubeMapNameCount)
	));
	m_textures_cube_map.emplace(tex.GetName(), tex);
	m_texCubeMapCount++;
	return m_textures_cube_map.at(tex.GetName());
}

inline Texture<TextureType::_2D>
ResourceMananger::LoadTextureFromFile(const char* path, MapType type, std::string_view name)
{
	Texture<TextureType::_2D> tex(name);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		tex.Generate(data, width, height, nrChannels, type);
		tex.SetTexParameter();
		stbi_image_free(data);
	} else
	{
#if _MSVC_LANG >= 202002L	/*CXX20*/
		std::cout << std::format("Texture failed to load at path: {}", path);
#else	
		std::cout << "Texture failed to load at path: " << path << std::endl;
#endif
		stbi_image_free(data);
	}
	return tex;

}
inline Texture<TextureType::_CUBE_MAP>
ResourceMananger::LoadTextureFromFile(const std::vector<const char*>& paths, std::string_view name)
{
	Texture<TextureType::_CUBE_MAP> tex(name);
	for (size_t i = 0; i < paths.size(); i++)
	{
		int width, height;
		unsigned char* data = stbi_load(paths.at(i), &width, &height, 0, 0);
		if (data)
		{
			tex.Generate(data, width, height, i);
			stbi_image_free(data);
		} else
		{
#if _MSVC_LANG >= 202002L	/*CXX20*/
			std::cout << std::format("Cubemap texture failed to load at path: {}", paths.at(i));
#else	
			std::cout << "Cubemap texture failed to load at path: " << paths.at(i) << std::endl;
#endif
			stbi_image_free(data);
		}
	}
	tex.SetTexParameter();
	return tex;
}




