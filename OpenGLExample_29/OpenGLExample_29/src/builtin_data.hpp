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
#include <string>

using BIGType = enum class BuiltInGeometryType
{
	CUBE,
	PLANE,
	VEGETATION,
	WINDOW,
	CUBE_WITH_NORMAL
};
using BIGVecParm = struct BuiltInGeometryVertexParameter
{
	bool TexCoord;
	bool Normal;
};
using BITList = enum class BuiltInTextureList
{
	CONTAINER,
	MARBLE,
	METAL,
	GRASS,
	WINDOW_TRANSPARENT
};
using BIGVecType		= std::map<BIGType, std::vector<float>>;
//using BIGVecIdxType	= std::map<BIGType, std::vector<float>>;	//indices about builtin Geometries, use with EBO, unfinished
using BIGVecParmType	= std::map<BIGType, BIGVecParm>;
using BITPathType		= std::map<BITList, const char*>;

using BIData = struct BuiltInData
{
	BuiltInData() = delete;
public:
	static const BITPathType	s_texturesPath;
	static const BIGVecType     s_vectices;
	static const BIGVecParmType s_parameters;
private:
	//tex path
	static const std::string containerTexPath;
	static const std::string marbleTexPath;
	static const std::string metalTexPath;
	static const std::string grassTexPath;
	static const std::string transparentWindowTexPath;

	//vertices
	static const std::vector<float> cubeVertices;
	static const std::vector<float> planeVertices;
	static const std::vector<float> vegetationVertices;
	static const std::vector<float> windowVertices;
	static const std::vector<float> cubeWithNormalVertices;

	//Parameter
	static const BIGVecParm cubeParm;
	static const BIGVecParm planeParm;
	static const BIGVecParm vegetationParm;
	static const BIGVecParm windowParm;
	static const BIGVecParm cubeWithNormalParm;
};

//---------------------------------------------------------------
//private
//---------------------------------------------------------------
inline const std::string BIData::containerTexPath				= "res/builtin/textures/others/container.jpg";
inline const std::string BIData::marbleTexPath					= "res/builtin/textures/others/marble.png";
inline const std::string BIData::metalTexPath					= "res/builtin/textures/others/metal.png";
inline const std::string BIData::grassTexPath					= "res/builtin/textures/others/grass.png";
inline const std::string BIData::transparentWindowTexPath		= "res/builtin/textures/others/blending_transparent_window.png";

inline const std::vector<float> BIData::cubeVertices = {
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
inline const std::vector<float> BIData::planeVertices = {
	//positions           //texture Coords
	 5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
	-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
	-5.0f, -0.5f, -5.0f,  0.0f, 1.0f,

	 5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
	-5.0f, -0.5f, -5.0f,  0.0f, 1.0f,
	 5.0f, -0.5f, -5.0f,  1.0f, 1.0f
};
inline const std::vector<float> BIData::vegetationVertices = {
	//positions         //texture Coords (swapped y coordinates because texture is flipped upside down)
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  1.0f,

	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f
};
inline const std::vector<float> BIData::windowVertices = {
	//positions         //texture Coords (swapped y coordinates because texture is flipped upside down)
	0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
	0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
	1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

	0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
	1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
	1.0f,  0.5f,  0.0f,  1.0f,  0.0f
};
inline const std::vector<float> BIData::cubeWithNormalVertices = {
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


inline const BIGVecParm BIData::cubeParm				= {true	, false};
inline const BIGVecParm BIData::planeParm				= {true	, false};
inline const BIGVecParm BIData::vegetationParm			= {true	, false};
inline const BIGVecParm BIData::windowParm				= {true	, false};
inline const BIGVecParm BIData::cubeWithNormalParm		= {false, true };

//---------------------------------------------------------------
//public
//---------------------------------------------------------------

inline const BIGVecType		BIData::s_vectices = {
	{BIGType::CUBE,                 BIData::cubeVertices},
	{BIGType::PLANE,                BIData::planeVertices},
	{BIGType::VEGETATION,           BIData::vegetationVertices},
	{BIGType::WINDOW,               BIData::windowVertices},
	{BIGType::CUBE_WITH_NORMAL,     BIData::cubeWithNormalVertices}
};

inline const BIGVecParmType BIData::s_parameters = {
	{BIGType::CUBE,					BIData::cubeParm},
	{BIGType::PLANE,				BIData::planeParm},
	{BIGType::VEGETATION,			BIData::vegetationParm},
	{BIGType::WINDOW,				BIData::windowParm},
	{BIGType::CUBE_WITH_NORMAL,		BIData::cubeWithNormalParm}
};

inline const BITPathType	BIData::s_texturesPath = {
	{BITList::CONTAINER,			BIData::containerTexPath.c_str()},
	{BITList::MARBLE,				BIData::marbleTexPath.c_str()},
	{BITList::METAL,				BIData::metalTexPath.c_str()},
	{BITList::GRASS,				BIData::grassTexPath.c_str()},
	{BITList::WINDOW_TRANSPARENT,	BIData::transparentWindowTexPath.c_str()}
};

