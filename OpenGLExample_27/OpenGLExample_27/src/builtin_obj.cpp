#define STB_IMAGE_IMPLEMENTATION
#include "../include/builtin_obj.h"

//---------------------------------------------------------------
//public
//---------------------------------------------------------------

BuiltInObject::BuiltInObject(BIOType objType)
{
	this->objVertices = BIOData::objVectices.at(objType);
	SetVAOandBuffers(objType);

	if (BIOData::objParameters.at(objType).Texture == false)
	{
		this->textureID = NULL;
	}
	else
	{
		this->textureID = LoadBuiltInObjectTexture(objType);
	}
}
BuiltInObject::~BuiltInObject() 
{}

unsigned int BuiltInObject::GetTexture()
{
	return this->textureID;
}

unsigned int BuiltInObject::GetVAO()
{
	return this->objVAO;
}

void BuiltInObject::BuiltInObjRender(GLShader& shader, 
									 glm::mat4& model, const glm::mat4 view, const glm::mat4 projection, 
									 bool whetherResetModelValue, unsigned int tex, unsigned int glTex)
{ 
	if (tex == NULL)
	{
		tex = this->textureID;
		if (tex == NULL)
		{
			std::cout << "Texture does not exist." << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	if (glTex == NULL)
		glTex = GL_TEXTURE_2D;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(glTex, tex);
	glBindVertexArray(this->objVAO);

	shader.SetMat4("model", model);
	shader.SetMat4("view", view);
	shader.SetMat4("projection", projection);
	if(whetherResetModelValue == true)
		model = glm::mat4(1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
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

void BuiltInObject::SetVAOandBuffers(BIOType objType)
{
	auto parm = BIOData::objParameters.at(objType);
	int stride = 3;
	if (parm.Normal == true)
		stride += 3;
	if (parm.TexCoord == true)
		stride += 2;

	glGenVertexArrays(1, &this->objVAO);
	glGenBuffers(1, &this->objVBO);
	glBindVertexArray(this->objVAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->objVBO);
	glBufferData(GL_ARRAY_BUFFER, this->objVertices.size() * sizeof(decltype(this->objVertices)::value_type), &this->objVertices.at(0), GL_STATIC_DRAW);

	int location = 0, offset = 3;
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, stride * sizeof(decltype(this->objVertices)::value_type), (void*)0);
	if (parm.Normal == true)
	{
		glEnableVertexAttribArray(++location);
		glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE,
			stride * sizeof(decltype(this->objVertices)::value_type), (void*)(offset * sizeof(decltype(this->objVertices)::value_type)));
		offset += 3;
	}
	if (parm.TexCoord == true)
	{
		glEnableVertexAttribArray(++location);
		glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE,
			stride * sizeof(decltype(this->objVertices)::value_type), (void*)(offset * sizeof(decltype(this->objVertices)::value_type)));
		offset += 2;
	}
	
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

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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
