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
#include "../include/builtin_obj_data.h"

class BuiltInObject
{
public:
	//this's stupid£¡BuiltInObject constructor's parameter only need a enum!
	BuiltInObject(BuiltInObjectType objType);
	~BuiltInObject() {}

	unsigned int texture;

	void BuiltInObjRender(GLShader& shader, const glm::mat4 model, const glm::mat4 view, const glm::mat4 projection);
	void DeleteVAO();
	void DeleteBuffers();

private:
	unsigned int objVAO;
	unsigned int objVBO;
	unsigned int objEBO;

	std::vector<float> objVertices;
	std::vector<float> objIndices;

	void SetVAO();

	unsigned int LoadBuiltInObjectTexture(BuiltInObjectType objType);
};

