#include "../include/builtin_obj_data.h"

//---------------------------------------------------------------
//private
//---------------------------------------------------------------

std::string BIOData::cubeTexPath = "res/marble.jpg";
std::string BIOData::planeTexPath = "res/metal.png";
std::string BIOData::vegetationTexPath = "res/grass.png";

std::vector<float> BIOData::cubeVertices = {
    //positions           //texture Coords
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
std::vector<float> BIOData::planeVertices = {
    //positions           //texture Coords
     5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
    -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 1.0f,

     5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 1.0f,
     5.0f, -0.5f, -5.0f,  1.0f, 1.0f
};
std::vector<float> BIOData::vegetationVertices = {
    // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  1.0f,

    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f
};

//---------------------------------------------------------------
//public
//---------------------------------------------------------------

OTexPath_t BIOData::objTexturesPath =
{
    {BIOType::OBJ_CUBE, cubeTexPath.c_str()},
    {BIOType::OBJ_PLANE, planeTexPath.c_str()},
    {BIOType::OBJ_VEGETATION, vegetationTexPath.c_str()}
};

OVec_t BIOData::objVectices =
{
    {BIOType::OBJ_CUBE, BIOData::cubeVertices},
    {BIOType::OBJ_PLANE, BIOData::planeVertices},
    {BIOType::OBJ_VEGETATION, BIOData::vegetationVertices}
};

