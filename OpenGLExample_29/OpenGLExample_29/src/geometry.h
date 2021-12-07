/*
* @Module Name: geometry.h
* @Auther: SnowyLake
* @Version: 1.0
* -------------------------------------------------------
* @Abstract:
*	This is the header file for create geometry class.
*	This class can create geometry by builtin data or
*	uesr define data.
*/
#pragma once
#include <vector>
#include <optional>
#include <string_view>
#include <format>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "texture.hpp"
#include "builtin_data.hpp"
#include "resource_manager.hpp"
using uint = unsigned int;
class Geometry
{
private:
	using GeomTexType = std::optional<Texture<TextureType::_2D>>;
public:
	Geometry(const std::vector<float>& vertices, const std::vector<uint>& vertOffset,
			 std::optional<std::reference_wrapper<const std::vector<float>>> indices = std::nullopt);
	Geometry(BIGType geom, bool haveIdx = false);	//indices about builtin Geometries, use with EBO, unfinished
	~Geometry();

	//disable copy cotr and copy op=
	Geometry(const Geometry&) = delete;
	Geometry& operator=(const Geometry&) = delete;

	void Render(Shader& shader,
				bool  whetherUseTexture = true,
				int   glDrawMode = GL_TRIANGLES, 
				float pixelSize = 1.0f,
				std::optional<uint> tex = std::nullopt, 
				std::optional<uint> gltex = std::nullopt);
	void Delete();

	unsigned int GetVAO() const;
	const GeomTexType& GetTexture() const;
	
	void SetTexture(const Texture<TextureType::_2D>& tex);
	void SetTexture(BITType tex);
private:
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_EBO;
	
	GeomTexType m_texture;
	unsigned int m_vertexCount;
	std::vector<float> m_vertices;
	std::optional<std::vector<float>> m_indices;

	void SetBuffers(BIGType type);
	void SetBuffers(const std::vector<uint>& vertOffset);
};

