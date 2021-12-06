/*
* @Module Name: builtin_data.hpp
* @Auther: SnowyLake
* @Version: 1.0
* -------------------------------------------------------
* @Abstract:
*	This is the header file of my built-in data.
*	This is just one of my attempts to implement unified
*	management of built-in objects.
*	This class is half-finished and ugly, and I'll be
*	refining and refactoring it later.
*/
#pragma once
#include <map>
#include <vector>
using BIGType = enum class BuiltInGeometryType
{
	CUBE,
	PLANE,
	VEGETATION,
	WINDOW,
	CUBE_WITH_NORMAL
};
using BIGData = struct BuiltInGeometryData
{
	bool texCoord;
	bool normal;
	std::vector<float> vertices;

	/*BuiltInGeometryData(bool t, bool n, const std::vector<float>& v)
		:texCoord(t), normal(n), vertices(v)
	{}*/
};
using BITType = enum class BuiltInTextureType
{
	CONTAINER,
	MARBLE,
	METAL,
	GRASS,
	WINDOW_TRANSPARENT
};
#define BITPath const char*

using BIGListType = std::map<BIGType, BIGData>;
using BITListType = std::map<BITType, BITPath>;

using BIData = struct BuiltInData
{
	BuiltInData() = delete;
public:
	static const BIGListType Geometries;
	static BITListType Textures;

private:
	//tex path
	static BITPath ContainerTexPath;
	static BITPath MarbleTexPath;
	static BITPath MetalTexPath;
	static BITPath GrassTexPath;
	static BITPath TransparentWindowTexPath;

	static const std::vector<float> CubeVertices;
	static const std::vector<float> PlaneVertices;
	static const std::vector<float> VegetationVertices;
	static const std::vector<float> WindowVertices;
	static const std::vector<float> CubeWithNormalVertices;

	static const BIGData Cube;
	static const BIGData Plane;
	static const BIGData Vegetation;
	static const BIGData Window;
	static const BIGData CubeWithNormal;
};

//---------------------------------------------------------------
//private
//---------------------------------------------------------------
inline BITPath BIData::ContainerTexPath				= "res/builtin/textures/others/container.jpg";
inline BITPath BIData::MarbleTexPath				= "res/builtin/textures/others/marble.png";
inline BITPath BIData::MetalTexPath					= "res/builtin/textures/others/metal.png";
inline BITPath BIData::GrassTexPath					= "res/builtin/textures/others/grass.png";
inline BITPath BIData::TransparentWindowTexPath		= "res/builtin/textures/others/blending_transparent_window.png";



inline const std::vector<float> BIData::CubeVertices = {
	//positions           //texture Coords
	 // Back face
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
	// Front face
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
	// Left face
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
	// Right face
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
	// Bottom face
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
	// Top face
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left      
};
inline const std::vector<float> BIData::PlaneVertices = {
	//positions           //texture Coords
	 5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
	-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
	-5.0f, -0.5f, -5.0f,  0.0f, 1.0f,

	 5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
	-5.0f, -0.5f, -5.0f,  0.0f, 1.0f,
	 5.0f, -0.5f, -5.0f,  1.0f, 1.0f
};
inline const std::vector<float> BIData::VegetationVertices = {
	//positions         //texture Coords (swapped y coordinates because texture is flipped upside down)
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  1.0f,

	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f
};
inline const std::vector<float> BIData::WindowVertices = {
	//positions         //texture Coords (swapped y coordinates because texture is flipped upside down)
	0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
	0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
	1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

	0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
	1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
	1.0f,  0.5f,  0.0f,  1.0f,  0.0f
};
inline const std::vector<float> BIData::CubeWithNormalVertices = {
	//positions         //normal
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

inline const BuiltInGeometryData BIData::Cube
{
	true, false,
	BIData::CubeVertices
};
inline const BIGData BIData::Plane
{
	true, false,
	BIData::PlaneVertices
};
inline const BIGData BIData::Vegetation
{
	true, false,
	BIData::VegetationVertices
};
inline const BIGData BIData::Window
{
	true, false,
	BIData::WindowVertices
};
inline const BIGData BIData::CubeWithNormal
{
	false, true,
	BIData::CubeWithNormalVertices
};
//---------------------------------------------------------------
//public
//---------------------------------------------------------------

inline const BIGListType BIData::Geometries = {
	{BIGType::CUBE,					BIData::Cube},
	{BIGType::PLANE,				BIData::Plane},
	{BIGType::VEGETATION,			BIData::Vegetation},
	{BIGType::WINDOW,				BIData::Window},
	{BIGType::CUBE_WITH_NORMAL,		BIData::CubeWithNormal}
};
inline BITListType BIData::Textures  = {
	{BITType::CONTAINER,			BIData::ContainerTexPath},
	{BITType::MARBLE,				BIData::MarbleTexPath},
	{BITType::METAL,				BIData::MetalTexPath},
	{BITType::GRASS,				BIData::GrassTexPath},
	{BITType::WINDOW_TRANSPARENT,	BIData::TransparentWindowTexPath}
};

