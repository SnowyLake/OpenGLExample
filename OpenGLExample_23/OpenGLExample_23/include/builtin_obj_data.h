/*
* @Module Name: builtin_obj_data.h
* @Auther: SnowyLake
* @Version: 0.2
* -------------------------------------------------------
* @Abstract:
*	This is the header file of my built-in objects' data.
*	This is just one of my attempts to implement unified
*	management of built-in objects.
*	This class is half-finished and ugly, and I'll be
*	refining and refactoring it later.
*/

#pragma once
#include <map>
#include <vector>
#include <string>

enum class BuiltInObjectType
{
    OBJ_CUBE,
    OBJ_PLANE,
};

class BuiltInObjectData
{
public:
    static std::map<BuiltInObjectType, const char*> objTexturesPath;
    static std::map<BuiltInObjectType, std::vector<float>> objVectices;

private:
    static std::string cubeTexPath;
    static std::string planeTexPath;

    static std::vector<float> cubeVertices;
    static std::vector<float> planeVertices;
};

