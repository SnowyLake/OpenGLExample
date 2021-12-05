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

#include "builtin_data.hpp"
#include "resource_manager.h"
class Geometry
{
public:
	Geometry(const std::vector<float>& vertices, unsigned int size[],
			 std::optional<std::reference_wrapper<const std::vector<float>>> indices = std::nullopt);
	Geometry(BIGType geom, bool haveIdx = false);	//indices about builtin Geometries, use with EBO, unfinished
	~Geometry();

	//disable copy cotr and copy op=
	Geometry(const Geometry&) = delete;
	Geometry& operator=(const Geometry&) = delete;

	void Render();
	void Delete();

	unsigned int GetVAO() const;
	unsigned int GetTexture() const;
	void SetTexture(std::string_view path);
	void SetTexture(BITList tex);
private:
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_EBO;
	unsigned int m_texture;

	std::vector<float> m_vertices;
	std::optional<std::vector<float>> m_indices;

	void SetBuffers(BIGType type);
	void SetBuffers(std::vector<float> vertices, unsigned int size[]);	//size[]的0号位设定为
	unsigned int LoadTextureFromFile(unsigned int tex, const char* path);
};

