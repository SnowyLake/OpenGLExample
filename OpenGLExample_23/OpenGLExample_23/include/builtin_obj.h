/*
* Module Name: builtin_obj.h
* Auther: SnowyLake
* Version: 0.1
* -------------------------------------------------------
* Abstract: 
*	This is the header file of my built-in objects.
*	This is just one of my attempts to implement unified 
*	management of built-in objects.
*	This class is half-finished and ugly, and I'll be 
*	refining and refactoring it later.
*/

#pragma once
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <gl_camera.h>
#include <gl_shader.h>

enum class BuiltInObjectType
{
	OBJ_CUBE,
	OBJ_PLANE,
};

class BuiltInObject
{
public:
	//this's stupid£¡BuiltInObject constructor's parameter only need a enum!
	BuiltInObject(BuiltInObjectType objType);
	~BuiltInObject() {}

	void BuiltInObjRender(GLShader& shader, const glm::mat4 view, const glm::mat4 projection, const glm::mat4 model);

private:
	unsigned int objVAO;
	unsigned int objVBO;
	unsigned int objEBO;

	std::vector<float> objVertices;
	std::vector<float> objIndices;

	void SetCubeVAO();
	void SetPlaneVAO();

	void LoadBuiltInObjectTexture(BuiltInObjectType objType);
};

