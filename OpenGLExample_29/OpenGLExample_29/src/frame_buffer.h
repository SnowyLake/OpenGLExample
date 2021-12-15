#pragma once
#include <tuple>
#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "window_manager.h"
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
	FrameBuffer(const WindowManager& win);
	~FrameBuffer();

	void CreateScreenQuad(uint quadNum);

	FrameBuffer& Bind();
	void UnBind();

	void Render(Shader& shader, uint num = 1, const glm::mat4 transform = glm::mat4(1.0f));
	void Update(const WindowManager& win);

	unsigned int GetTexBuffer() const;
	void Destory();

private:
	uint m_width;
	uint m_height;
	uint m_FBO;
	uint m_RBO;
	uint m_texBuffer;
	bool m_whetherCreateScreenQuad = false;

	std::vector<Quad> quad;

	//create a color attachment texture
	void SetTexBuffer(unsigned int width, unsigned int height);
	//create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	void SetRBO(unsigned int width, unsigned int height);
};
