#pragma once
#include <map>
#include <vector>
#include <tuple>
#include <optional>
#include <string>
#include <string_view>


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