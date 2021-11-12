#pragma once
#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <gl_shader.h>

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
class FramebuffersManager
{
public:
	FramebuffersManager(GLFWwindow* window);
	~FramebuffersManager();

	void CreateScreenQuad(unsigned int quadNum);

	void Bind();
	void UnBind();
	void Render(GLShader shader, unsigned int num, const glm::mat4 transform);

	void Delete();

private:
	//framebuffers
	unsigned int FBO;
	unsigned int RBO;
	unsigned int texColorbuffer;
	bool whetherCreateScreenQuad = false;

	std::vector<Quad> quad;

	//create a color attachment texture
	void SetTexColorBuffer(unsigned int width, unsigned int height);
	//create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	void SetRBO(unsigned int width, unsigned int height);
};
