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

#include "window_manager.h"
#include "gl_camera.h"

#include "geometry.h"
#include "model.h"
#include "skybox.h"
#include "frame_buffer.h"

#include "uniform_buffer.h"
#include "resource_manager.hpp"
#include "utility.hpp"
#include "render_to.hpp"

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

//skybox
std::vector<const char*> paths = {
	"res/builtin/textures/skybox/right.jpg",
	"res/builtin/textures/skybox/left.jpg",
	"res/builtin/textures/skybox/top.jpg",
	"res/builtin/textures/skybox/bottom.jpg",
	"res/builtin/textures/skybox/front.jpg",
	"res/builtin/textures/skybox/back.jpg"
};

int main()
{
	//create camera
	GLCamera camera(glm::vec3(0.0f, 10.0f, 20.0f));
	//create window
	WindowManager window(SCR_WIDTH, SCR_HEIGHT, EXAMPLE_NAME, &camera);
	window.SetCallback();

	//configure global OpenGL state
	//-----------------------------
	glEnable(GL_DEPTH_TEST);

	//shaders
	//-------
	auto& resMgr = ResourceMananger::GetInstance();
	auto& skyboxShader = resMgr.LoadShader("res/builtin/shaders/skybox.vert",
										   "res/builtin/shaders/skybox.frag",
										   nullptr,
										   "skybox");

	auto& screenDefaultShader = resMgr.LoadShader(PostProcessShaders::DefaultVert,
												  PostProcessShaders::DefaultFrag,
												  nullptr,
												  "postproc");
	
	/*auto& geomTestShader = resMgr.LoadShader("res/shaders/gs_test.vert",
											 "res/shaders/gs_test.frag",
											 "res/shaders/gs_test.geom",
											 "geometry_test");*/

	auto& geomTestShader = resMgr.LoadShader("res/shaders/gs_test_model_explode.vert",
											 "res/shaders/gs_test_model_explode.frag",
											 "res/shaders/gs_test_model_explode.geom",
											 "geometry_test_model_explode");

	//shader config
	skyboxShader.Use().SetInt("skyboxTex", 0);
	screenDefaultShader.Use().SetInt("screenTex", 0);

	//create scene objects
	Geometry points(pointsVertices, {2u,3u});
	Model nanosuit("res/builtin/model/nanosuit/nanosuit.obj");
	Skybox skybox(resMgr.LoadTexture(paths, "skybox"));
	/*Geometry cube(BIGType::CUBE);
	resMgr.LoadTexture(BIData::Textures.at(BITType::CONTAINER), MapType::NONE);
	cube.SetTexture(resMgr.GetTexture<TextureType::_2D>("texture_1"));*/

	//geomTestShader.
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
		glClearColor(0.1f, 0.1f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//MVP
		auto model = glm::mat4(1.0f);
		auto view = camera.GetViewMatrix();
		auto [_width, _height] = GetFramebufferSize(window.Get());
		auto projection = glm::perspective(glm::radians(camera.Zoom),
										   static_cast<float>(_width) / static_cast<float>(_height),
										   0.1f, 100.0f);

		//render
		//points.Render(geomTestShader, false, GL_POINTS);

		geomTestShader.Use()
			.SetMat4("model", model)
			.SetMat4("view", view)
			.SetMat4("projection", projection)
			.SetFloat("time", static_cast<float>(glfwGetTime()))
			>> RenderTo(nanosuit);
		//nanosuit.Render(geomTestShader);
	
		skyboxShader.Use()
			.SetMat4("view", glm::mat4(glm::mat3(view)))
			.SetMat4("projection", projection)
			>> RenderTo(skybox);
		//skybox.Render(skyboxShader);

		/*unbind*/ defaultSpace.UnBind();
		//----------------------------------------------------------------
		
		//clear all relevant buffers
		glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		screenDefaultShader.Use() >> RenderTo(defaultSpace);
		//defaultSpace.Render(screenDefaultShader);

		window.UpData();
	}
	points.Destory();
	defaultSpace.Destory();
	skybox.Destory();
	window.Destory();

	return 0;
}