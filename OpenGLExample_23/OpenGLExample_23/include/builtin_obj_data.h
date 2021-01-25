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

