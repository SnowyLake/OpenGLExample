#pragma once
#include <vector>
#include <iostream>

#include <gl_shader.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
class FramebuffersManager
{
public:
	FramebuffersManager(unsigned int width, unsigned int height);
	~FramebuffersManager();

	void CreateScreenQuad();

	void Bind();
	void UnBind();
	void Render(GLShader shader);

	void Delete();

private:
	//framebuffers
	unsigned int FBO;
	unsigned int RBO;
	unsigned int texColorbuffer;
	bool whetherCreateScreenQuad = false;

	static std::vector<float> quadVertices;
	unsigned int quadVAO, quadVBO;

	//create a color attachment texture
	void SetTexColorBuffer(unsigned int width, unsigned int height);
	//create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	void SetRBO(unsigned int width, unsigned int height);
};
