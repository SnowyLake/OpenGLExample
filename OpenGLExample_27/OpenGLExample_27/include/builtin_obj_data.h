#pragma once
/*
* @Module Name: builtin_obj_data.h
* @Auther: SnowyLake
* @Version: 0.3
* -------------------------------------------------------
* @Abstract:
*	This is the header file of my built-in objects' data.
*	This is just one of my attempts to implement unified
*	management of built-in objects.
*	This class is half-finished and ugly, and I'll be
*	refining and refactoring it later.
*/


#include <map>
#include <vector>
#include <string>

using BIOType = enum class BuiltInObjectType
{
    OBJ_CUBE,
    OBJ_PLANE,
    OBJ_VEGETATION,
    OBJ_WINDOW,
    OBJ_CUBE_WITH_NORMAL
};
using BIOParm = struct BuiltInObjectParameter
{
    bool Texture;
    bool TexCoord;
    bool Normal;
    bool EBO;
};

using OTexPath_t = const std::map<BIOType, const char*>;
using OVec_t = const std::map<BIOType, std::vector<float>>;
using OParm_t = const std::map<BIOType, BIOParm>;

using BIOData = struct BuiltInObjectData
{

    static OTexPath_t objTexturesPath;
    static OVec_t objVectices;
    static OParm_t objParameters;


    //tex path
    static const std::string cubeTexPath;
    static const std::string planeTexPath;
    static const std::string vegetationTexPath;
    static const std::string windowTexPath;

    //vertices
    static const std::vector<float> cubeVertices;
    static const std::vector<float> planeVertices;
    static const std::vector<float> vegetationVertices;
    static const std::vector<float> windowVertices;
    static const std::vector<float> cubeWithNormalVertices;

    //Parameter
    static const BIOParm cubeParm;
    static const BIOParm planeParm;
    static const BIOParm vegetationParm;
    static const BIOParm windowParm;
    static const BIOParm cubeWithNormalParm;
};

