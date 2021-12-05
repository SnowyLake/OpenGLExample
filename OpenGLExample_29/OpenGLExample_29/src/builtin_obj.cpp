#define STB_IMAGE_IMPLEMENTATION
#include "builtin_obj.h"

//---------------------------------------------------------------
//public
//---------------------------------------------------------------

BuiltInObject::BuiltInObject(BIOType objType)
{
	m_objVertices = BIOData::s_objVectices.at(objType);
	SetVAOandBuffers(objType);

	if (BIOData::s_objParameters.at(objType).Texture == false)
	{
		m_textureID = NULL;
	}
	else
	{
		m_textureID = LoadBuiltInObjectTexture(objType);
	}
}
BuiltInObject::~BuiltInObject() 
{}

unsigned int BuiltInObject::GetTexture() const
{
	return m_textureID;
}

unsigned int BuiltInObject::GetVAO() const
{
	return m_objVAO;
}

void BuiltInObject::BuiltInObjRender(GLShader& shader, 
									 glm::mat4& model, const glm::mat4 view, const glm::mat4 projection, 
									 bool whetherResetModelValue, unsigned int tex, unsigned int glTex)
{ 
	if (tex == NULL)
	{
		tex = m_textureID;
		if (tex == NULL)
		{
			std::cout << "Texture does not exist." << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	if (glTex == NULL)
		glTex = GL_TEXTURE_2D;

	glBindVertexArray(m_objVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(glTex, tex);
	
	shader.SetMat4("model", model)
		.SetMat4("view", view)
		.SetMat4("projection", projection);

	if(whetherResetModelValue == true)
		model = glm::mat4(1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(0);
}

void BuiltInObject::BuiltInObjRender(GLShader& shader, glm::mat4& model, bool whetherResetModelValue, unsigned int tex, unsigned int glTex)
{
	if (tex == NULL)
	{
		tex = m_textureID;
		if (tex == NULL)
		{
			std::cout << "Texture does not exist." << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	if (glTex == NULL)
		glTex = GL_TEXTURE_2D;

	glBindVertexArray(m_objVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(glTex, tex);

	shader.SetMat4("model", model);
	if (whetherResetModelValue == true)
		model = glm::mat4(1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(0);
}



void BuiltInObject::Delete()
{
	glDeleteVertexArrays(1, &m_objVAO);
	glDeleteBuffers(1, &m_objVBO);
	glDeleteBuffers(1, &m_objEBO);
}

//---------------------------------------------------------------
//private
//---------------------------------------------------------------

void BuiltInObject::SetVAOandBuffers(BIOType objType)
{
	auto parm = BIOData::s_objParameters.at(objType);
	int stride = 3;
	if (parm.Normal == true)
		stride += 3;
	if (parm.TexCoord == true)
		stride += 2;

	glGenVertexArrays(1, &m_objVAO);
	glGenBuffers(1, &m_objVBO);
	glBindVertexArray(m_objVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_objVBO);
	glBufferData(GL_ARRAY_BUFFER, m_objVertices.size() * sizeof(decltype(m_objVertices)::value_type), &m_objVertices.at(0), GL_STATIC_DRAW);

	int location = 0, offset = 3;
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, stride * sizeof(decltype(m_objVertices)::value_type), (void*)0);
	if (parm.Normal == true)
	{
		glEnableVertexAttribArray(++location);
		glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE,
			stride * sizeof(decltype(m_objVertices)::value_type), (void*)(offset * sizeof(decltype(m_objVertices)::value_type)));
		offset += 3;
	}
	if (parm.TexCoord == true)
	{
		glEnableVertexAttribArray(++location);
		glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE,
			stride * sizeof(decltype(m_objVertices)::value_type), (void*)(offset * sizeof(decltype(m_objVertices)::value_type)));
		offset += 2;
	}
	
	glBindVertexArray(0);
	m_objEBO = 0;
}

unsigned int BuiltInObject::LoadBuiltInObjectTexture(BIOType objType)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	const char* path = BIOData::s_objTexturesPath.at(objType);

	//stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);

	if(data)
	{
		GLenum format = NULL;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
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
