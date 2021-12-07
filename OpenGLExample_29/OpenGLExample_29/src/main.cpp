#define STB_IMAGE_IMPLEMENTATION
#include <map>
#include <vector>
#include <string>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "gl_camera.h"

#include "window_manager.h"

#include "geometry.h"
#include "model.h"
#include "skybox.h"

#include "frame_buffer.h"
#include "uniform_buffer.h"

#include "resource_manager.hpp"
#include "utility.hpp"

#include "../res/builtin/shaders/post_process/post_process_shaders.hpp"

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "assimp-vc143-mt.lib")

//setting
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;
const unsigned int BINDING_POINT_0 = 0;
const char* EXAMPLE_NAME = "Geometry Shader";

//points
std::vector<float> pointsVertices = {
	-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-left
	 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // top-right
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
	-0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // bottom-left
};

int main()
{
	//create window
	WindowManager window(SCR_WIDTH, SCR_HEIGHT, EXAMPLE_NAME);
	window.SetCallback();

	//configure global OpenGL state
	//-----------------------------
	glEnable(GL_DEPTH_TEST);

	//shaders
	//-------
	auto& resMgr = ResourceMananger::GetInstance();
	auto& screenDefaultShader = resMgr.LoadShader(PostProcessShaders::DefaultVert,
												  PostProcessShaders::DefaultFrag,
												  nullptr,
												  "postproc");
	auto& geomTestShader = resMgr.LoadShader("res/shaders/gs_test.vert",
											 "res/shaders/gs_test.frag",
											 "res/shaders/gs_test.geom",
											 "geometry_test");

	//shader config
	screenDefaultShader.Use().SetInt("screenTex", 0);

	//create scene objects
	Geometry points(pointsVertices, std::vector<unsigned int>{2,3});

	//draw as wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	window.Show(100, 100);

	//create framebuffers
	FrameBuffer defaultSpace(window.Get());
	defaultSpace.CreateScreenQuad(1);

	//render loop
	//-----------
	while (!glfwWindowShouldClose(window.Get()))
	{
		window.ProcessInput();
		
		//defaultSpace
		//----------------------------------------------------------------
		/*bind  */ defaultSpace.Bind();
		
		//make sure we clear the framebuffer's content
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//render
		points.Render(geomTestShader, false, GL_POINTS, 1.0f);

		/*unbind*/ defaultSpace.UnBind();
		//----------------------------------------------------------------
		
		//clear all relevant buffers
		//glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);

		defaultSpace.Render(screenDefaultShader);

		window.UpData();
	}
	points.Destory();
	defaultSpace.Destory();
	window.Destory();

	return 0;
}