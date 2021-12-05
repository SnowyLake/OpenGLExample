#pragma once
#include<string>
#include<vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "gl_shader.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 tangent;
	glm::vec3 bitangent;
};
//TODO: _Texture will be remove
struct _Texture
{
	unsigned int id = NULL;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	//mesh data
	std::vector<Vertex>			vertices;
	std::vector<unsigned int>	indices;
	std::vector<_Texture>		textures;
	unsigned int VAO;

	//constructor
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<_Texture> textures);

	//render the mesh
	void Render(GLShader& shader);

private:
	//render data
	unsigned int VBO, EBO;

	//initializes all the buffer objects/arrays
	void SetupMesh();
};

