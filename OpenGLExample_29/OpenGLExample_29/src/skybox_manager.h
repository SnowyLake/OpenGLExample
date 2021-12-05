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

class SkyboxManager
{
public:
	SkyboxManager(std::vector<std::string> faces);
	~SkyboxManager();

	unsigned int GetTexture() const;
	unsigned int GetVAO() const;

	void Render(Shader shader, const glm::mat4 view, const glm::mat4 projection);
	void Delete();

private:
	unsigned int m_cubemapTexID;
	unsigned int m_skyboxVAO;
	unsigned int m_skyboxVBO;
	static std::vector<float> skyboxVertices;

	void SetVAOandBuffers();
	unsigned int LoadCubemap(std::vector<std::string> faces);


};
