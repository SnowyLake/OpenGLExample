#include "../include/builtin_obj.h"
#include "../include/builtin_obj_data.h"

BuiltInObject::BuiltInObject(BuiltInObjectType objType)
{
	switch(objType)
	{
	case BuiltInObjectType::OBJ_CUBE:
		objVertices = cubeVertices;
		SetCubeVAO();
		break;
	case BuiltInObjectType::OBJ_PLANE:
		objVertices = planeVertices;
		SetPlaneVAO();
		break;
	default:
		break;
	}
}

void BuiltInObject::BuiltInObjRender(GLShader& shader, const glm::mat4 view, const glm::mat4 projection, const glm::mat4 model)
{
}

void BuiltInObject::SetCubeVAO()
{
	glGenVertexArrays(1, &objVAO);
	glGenBuffers(1, &objVBO);
	glBindVertexArray(objVAO);
	glBindBuffer(GL_ARRAY_BUFFER, objVBO);
	glBufferData(GL_ARRAY_BUFFER, objVertices.size() * sizeof(float), &objVertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);
	objEBO = 0;
}

void BuiltInObject::SetPlaneVAO()
{
	glGenVertexArrays(1, &objVAO);
	glGenBuffers(1, &objVBO);
	glBindVertexArray(objVAO);
	glBindBuffer(GL_ARRAY_BUFFER, objVBO);
	glBufferData(GL_ARRAY_BUFFER, objVertices.size() * sizeof(float), &objVertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);
	objEBO = 0;
}

void BuiltInObject::LoadBuiltInObjectTexture(BuiltInObjectType objType)
{

}
