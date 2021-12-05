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
#include <stb_image.h>

#include "gl_camera.h"
#include "gl_shader.h"
//#include "builtin_obj_data.hpp"
//
//class BuiltInObject
//{
//public:
//	BuiltInObject(BIOType objType);
//	~BuiltInObject();
//	unsigned int GetTexture() const;
//	unsigned int GetVAO() const;
//
//	void BuiltInObjRender(GLShader& shader, 
//						  glm::mat4& model, const glm::mat4 view, const glm::mat4 projection, 
//						  bool whetherResetModelValue, unsigned int tex = NULL, unsigned int glTex = NULL);
//	void BuiltInObjRender(GLShader& shader, glm::mat4& model,
//						  bool whetherResetModelValue, unsigned int tex = NULL, unsigned int glTex = NULL);
//
//	void Delete();
//
//private:
//	unsigned int m_textureID;
//	unsigned int m_objVAO;
//	unsigned int m_objVBO;
//	unsigned int m_objEBO;
//
//	std::vector<float> m_objVertices;
//	std::vector<float> m_objIndices;
//
//	void SetVAOandBuffers(BIOType objType);
//	unsigned int LoadBuiltInObjectTexture(BIOType objType);
//};

