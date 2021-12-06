#pragma once
#include <vector>
#include <format>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "texture.hpp"

class Skybox
{
public:
	Skybox(const Texture<TextureType::_CUBE_MAP>& tex);
	~Skybox();

	Texture<TextureType::_CUBE_MAP>& GetTexture();
	unsigned int GetVAO() const;

	void Render(Shader shader, const glm::mat4 view, const glm::mat4 projection);
	void Delete();

private:
	Texture<TextureType::_CUBE_MAP> m_texture;
	unsigned int m_VAO;
	unsigned int m_VBO;
	static std::vector<float> skyboxVertices;

	void SetVAOandBuffers();
	//unsigned int LoadCubemap(std::vector<std::string> faces);
};
