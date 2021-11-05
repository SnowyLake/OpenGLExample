#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
#include "../include/builtin_obj.h"

//---------------------------------------------------------------
//public
//---------------------------------------------------------------

BuiltInObject::BuiltInObject(BIOType objType)
{
	this->objVertices = BIOData::objVectices.at(objType);
	SetVAOandBuffers();
	this->texture = LoadBuiltInObjectTexture(objType);
}
BuiltInObject::~BuiltInObject() 
{}

void BuiltInObject::BuiltInObjRender(GLShader& shader, const glm::mat4 model, const glm::mat4 view, const glm::mat4 projection)
{
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->objVAO);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	shader.Use();
	shader.SetMat4("model", model);
	shader.SetMat4("view", view);
	shader.SetMat4("projection", projection);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void BuiltInObject::BuiltInObjRender(GLShader& shader, glm::mat4& model, const glm::mat4 view, const glm::mat4 projection, bool whetherResetModelValue)
{ 
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->objVAO);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	shader.Use();
	shader.SetMat4("model", model);
	shader.SetMat4("view", view);
	shader.SetMat4("projection", projection);
	if(whetherResetModelValue == true)
		model = glm::mat4(1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}


void BuiltInObject::Delete()
{
	glDeleteVertexArrays(1, &this->objVAO);
	glDeleteBuffers(1, &this->objVBO);
	glDeleteBuffers(1, &this->objEBO);
}

//---------------------------------------------------------------
//private
//---------------------------------------------------------------

void BuiltInObject::SetVAOandBuffers()
{
	glGenVertexArrays(1, &this->objVAO);
	glGenBuffers(1, &this->objVBO);
	glBindVertexArray(this->objVAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->objVBO);
	glBufferData(GL_ARRAY_BUFFER, this->objVertices.size() * sizeof(decltype(this->objVertices)::value_type), &this->objVertices.at(0), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(decltype(this->objVertices)::value_type), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(decltype(this->objVertices)::value_type), (void*)(3 * sizeof(decltype(this->objVertices)::value_type)));
	glBindVertexArray(0);
	this->objEBO = 0;
}

unsigned int BuiltInObject::LoadBuiltInObjectTexture(BIOType objType)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	const char* path = BIOData::objTexturesPath.at(objType);

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);

	if(data)
	{
		GLenum format = NULL;
		if(nrComponents == 1)
			format = GL_RED;
		else if(nrComponents == 3)
			format = GL_RGB;
		else if(nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format = GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format = GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << "\n";
		stbi_image_free(data);
	}
	return textureID;
}
