#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <optional>
#include <string>
#include <string_view>

#include <stb_image.h>

#include "texture.hpp"
#include "Dev_Texture.h"
#include "utility.hpp"
#include "shader.h"
using TexSPtr_t = std::shared_ptr<Dev_Texture>;
class ResourceMananger
{
public:
	static ResourceMananger& GetInstance();

	//shader
	Shader& LoadShader(const char* vPath,
					   const char* fPath,
					   const char* gPath = nullptr,
					   std::optional<std::string_view> name = std::nullopt);

	Shader& GetShader(const std::string& shaderName);
	uint GetShaderCount() const;

	//texture
	TexSPtr_t LoadTexture(const char* path);
	TexSPtr_t GetTexture(const std::string& path);
	uint GetTextureCount() const;
	
private:
	ResourceMananger();
	~ResourceMananger() = default;
	ResourceMananger(const ResourceMananger&) = delete;
	ResourceMananger(ResourceMananger&&) = delete;
	ResourceMananger& operator=(const ResourceMananger&) = delete;
	ResourceMananger& operator=(ResourceMananger&&) = delete;

	//对象保存
	std::unordered_map<std::string, Shader> m_shaders;
	std::unordered_map<std::string, TexSPtr_t> m_textures;

	//默认命名编号
	uint m_shaderDefaultNameCount;

	Shader LoadShaderFromFile(const char* vPath,
							  const char* fPath,
							  const char* gPath,
							  std::string_view name);

	TexSPtr_t LoadTextureFromFile(const FileNameInfo& info);
};

inline ResourceMananger& ResourceMananger::GetInstance()
{
	static ResourceMananger instance;
	return instance;
}
inline ResourceMananger::ResourceMananger(): m_shaderDefaultNameCount(0)
{}

//shader
//------------------------
inline Shader& ResourceMananger::GetShader(const std::string& shaderName)
{
	assert(m_shaders.contains(shaderName));	//检测shaderName是否存在
	return m_shaders.at(shaderName);
}
inline uint ResourceMananger::GetShaderCount() const
{
	return m_shaders.size();
}
inline Shader& ResourceMananger::LoadShader(const char* vPath,
											const char* fPath,
											const char* gPath /* = nullptr*/,
											std::optional<std::string_view> aName /*= std::nullopt*/)
{
	std::string name;
	aName.has_value() ? name = aName.value() : name = std::format("shader_{}", ++m_shaderDefaultNameCount);
	//检测是否与已有对象重名
	if (aName.has_value() && m_shaders.contains(name))
	{
		int count = 2;
		std::string _name = name;
		while (m_shaders.contains(_name))
		{
			_name = std::format("{}_{}", name, count++);
		}
		name = _name;
	}
	Shader shader = LoadShaderFromFile(vPath, fPath, gPath, name);
	m_shaders.emplace(shader.GetName(), shader);
	return m_shaders.at(shader.GetName());
}

inline Shader ResourceMananger::LoadShaderFromFile(const char* vPath,
												   const char* fPath,
												   const char* gPath,
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
TexSPtr_t ResourceMananger::GetTexture(const std::string& path)
{
	assert(m_textures.contains(path));
	return m_textures.at(path);
}
uint ResourceMananger::GetTextureCount() const
{
	return m_textures.size();
}

TexSPtr_t ResourceMananger::LoadTexture(const char* path)
{
	FileNameInfo info(path);
	//检测是否已加载
	bool skip = false;
	for (auto&& [keyFile, valTex] : m_textures)
	{
		if (keyFile == info.GetFile())
		{
			skip = true;
			return valTex;
			break;
		}
	}
	if (!skip)
	{
		auto tex = LoadTextureFromFile(info);
		m_textures.emplace(path, tex);
		std::cout << tex.use_count();
		return m_textures.at(path);
	}
}
//inline Texture<TextureType::_CUBE_MAP>&
//ResourceMananger::LoadTexture(const std::vector<const char*>& paths,
//							  std::optional<std::string_view> name /*= std::nullopt*/,
//							  bool whetherDetectRepeatLoading /*= true*/)
//{
//	//TODO: 需要检测是否与已有对象重名
//	auto tex = LoadTextureFromFile(paths, name.has_value() ?
//								   name.value() : std::format("texture_cubemap_{}", ++m_shaderDefaultNameCount));
//	m_texturesCubeMap.emplace(tex.GetName(), tex);
//	return m_texturesCubeMap.at(tex.GetName());
//}

TexSPtr_t ResourceMananger::LoadTextureFromFile(const FileNameInfo& info)
{
	TexSPtr_t textureSPtr = std::make_shared<Dev_Texture>(info);
	//Dev_Texture texture(info);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(info.GetFile().c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		textureSPtr->SetParameter(width, height, nrChannels, data);
		data = nullptr;	//data已由 std::unique_ptr<uchar> Texture::m_data 管理
		stbi_image_free(data);
	} else
	{
#if _MSVC_LANG >= 202002L	/*CXX20*/
		std::cout << std::format("Texture failed to load at path: {}\n", info.GetFile());
#else	
		std::cout << "Texture failed to load at path: " << info.GetFile() << << '\n' std::endl;
#endif
		stbi_image_free(data);
	}
	return textureSPtr;
}
//inline Texture<TextureType::_CUBE_MAP>
//ResourceMananger::LoadTextureFromFile(const std::vector<const char*>& paths, std::string_view name)
//{
//	Texture<TextureType::_CUBE_MAP> tex(paths, name);
//	for (size_t i = 0; i < paths.size(); i++)
//	{
//		int width, height;
//		unsigned char* data = stbi_load(paths.at(i), &width, &height, 0, 0);
//		if (data)
//		{
//			tex.Generate(data, width, height, i);
//			stbi_image_free(data);
//		} else
//		{
//#if _MSVC_LANG >= 202002L	/*CXX20*/
//			std::cout << std::format("Cubemap texture failed to load at path: {}\n", paths.at(i));
//#else	
//			std::cout << "Cubemap texture failed to load at path: " << paths.at(i) << '\n' << std::endl;
//#endif
//			stbi_image_free(data);
//		}
//	}
//	tex.SetTexParameter();
//	return tex;
//}




