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
#include "Dev_Map.h"
#include "builtin_data.hpp"
#include "resource_manager.hpp"
using uint = unsigned int;
class Geometry
{
public:
	Geometry(const std::vector<float>& vertices, const std::vector<uint>& vertOffset,
			 std::optional<std::reference_wrapper<const std::vector<float>>> indices = std::nullopt);
	Geometry(BIGType geom, bool haveIdx = false);	//indices about builtin Geometries, use with EBO, unfinished
	~Geometry();

	Geometry(const Geometry&) = default;
	Geometry(Geometry&&) = default;
	Geometry& operator=(const Geometry&) = default;
	Geometry& operator=(Geometry&&) = default;

	void Render(Shader& shader,
				bool  whetherUseMap = true,
				int   glDrawMode = GL_TRIANGLES, 
				float pixelSize = 1.0f,
				std::optional<uint> map = std::nullopt,
				std::optional<uint> glTexType = std::nullopt);
	void Destory();

	unsigned int GetVAO() const;
	const std::optional<Dev_Map>& GetMap() const;
	
	void SetMap(const Dev_Map& map);
	void SetMap(Dev_Map&& map);
	void SetMap(BITType tex, MapType type);
private:
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_EBO;
	
	std::optional<Dev_Map> m_map;
	unsigned int m_vertexCount;
	std::vector<float> m_vertices;
	std::optional<std::vector<float>> m_indices;

	void SetBuffers(BIGType type);
	void SetBuffers(const std::vector<uint>& vertOffset);
};

