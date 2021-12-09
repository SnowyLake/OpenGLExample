#pragma once
#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utility.hpp"
#include "shader.h"

struct Quad
{
	unsigned int VAO;
	unsigned int VBO;
	static std::vector<float> quadVertices;

	Quad(unsigned int VAO, unsigned int VBO)
	{
		this->VAO = VAO;
		this->VBO = VBO;
	}

};
class FrameBuffer
{
public:
	FrameBuffer(GLFWwindow* window);
	~FrameBuffer();

	void CreateScreenQuad(unsigned int quadNum);

	void Bind();
	void UnBind();
	void Render(Shader& shader, unsigned int num = 1, const glm::mat4 transform = glm::mat4(1.0f));

	unsigned int GetTexColorBuffer() const;
	void Destory();

private:
	//framebuffers
	unsigned int m_FBO;
	unsigned int m_RBO;
	unsigned int m_texColorbuffer;
	bool m_whetherCreateScreenQuad = false;

	std::vector<Quad> quad;

	//create a color attachment texture
	void SetTexColorBuffer(unsigned int width, unsigned int height);
	//create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	void SetRBO(unsigned int width, unsigned int height);
};
