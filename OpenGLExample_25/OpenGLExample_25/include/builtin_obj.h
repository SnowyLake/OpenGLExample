/*
* @Module Name: builtin_obj.h
* @Auther: SnowyLake
* @Version: 0.2
* -------------------------------------------------------
* @Abstract: 
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
	unsigned int texture;

	//this's stupid!
	//BuiltInObject constructor's parameter only need a enum!
	BuiltInObject(BIOType objType);
	~BuiltInObject();

	//default not reset model matrix value
	void BuiltInObjRender(GLShader& shader, const glm::mat4 model, const glm::mat4 view, const glm::mat4 projection);
	//explicitly specify whether to reset model matrix value to glm::mat4(1.0)
	void BuiltInObjRender(GLShader& shader, glm::mat4& model, const glm::mat4 view, const glm::mat4 projection, bool whetherResetModelValue);

	void DeleteVAO();
	void DeleteBuffers();

private:
	unsigned int objVAO;
	unsigned int objVBO;
	unsigned int objEBO;

	std::vector<float> objVertices;
	std::vector<float> objIndices;

	void SetVAOandBuffers();
	unsigned int LoadBuiltInObjectTexture(BIOType objType);
};

