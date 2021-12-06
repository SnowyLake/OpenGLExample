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
#include "utility.hpp"
#include "model.h"
#include "texture.hpp"
#include "window_manager.h"
#include "skybox_manager.h"

#include "resource_manager.hpp"
#include "framebuffers_manager.h"
#include "uniform_buffer_manager.h"
#include "geometry.h"

#include "../res/builtin/shaders/post_process/post_process_shaders.hpp"

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "assimp-vc143-mt.lib")

//setting
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;
const unsigned int BINDING_POINT_0 = 0;
const char* EXAMPLE_NAME = "Geometry Shader";

//camera
GLCamera camera(glm::vec3(0.0f, 0.0f, 10.0f));

//skybox
std::vector<const char*> skyboxTexs = {
	"res/builtin/textures/skybox/right.jpg",
	"res/builtin/textures/skybox/left.jpg",
	"res/builtin/textures/skybox/top.jpg",
	"res/builtin/textures/skybox/bottom.jpg",
	"res/builtin/textures/skybox/front.jpg",
	"res/builtin/textures/skybox/back.jpg"
};

int main()
{
	//create window
	WindowManager windowMgr(&camera, SCR_WIDTH, SCR_HEIGHT, EXAMPLE_NAME);
	windowMgr.SetCallback();

	//configure global OpenGL state
	//-----------------------------
	glEnable(GL_DEPTH_TEST);

	//shaders
	//-------
	auto& resMgr = ResourceMananger::GetInstance();
	auto& skyboxShader = resMgr.LoadShader("res/builtin/shaders/skybox.vert", "res/builtin/shaders/skybox.frag", nullptr, "skybox");
	auto& screenDefaultShader = resMgr.LoadShader(PostProcessShaders::DefaultVert, PostProcessShaders::DefaultFrag, nullptr, "postproc");
	auto& defaultShader = resMgr.LoadShader("res/builtin/shaders/default.vert", "res/builtin/shaders/default.frag", nullptr, "default");
	//shader config
	//-------------
	UniformBlockBind(defaultShader, "Matrices", BINDING_POINT_0);
	defaultShader.Use()
		.SetInt("texture1", 0);
	skyboxShader.Use()
		.SetInt("skyboxTex", 0);
	screenDefaultShader.Use()
		.SetInt("screenTex", 0);

	//create UBO
	//----------
	UniformBufferManager UBO(2 * sizeof(glm::mat4));
	UBO.BindPoint(BINDING_POINT_0);
	auto [_width, _height] = GetFramebufferSize(windowMgr.GetWindow());
	auto projection = glm::perspective(glm::radians(camera.Zoom), static_cast<float>(_width) / static_cast<float>(_height), 0.1f, 100.0f);
	UBO.SetSubData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(projection));
	//create scene objects
	//--------------------
	Geometry cube(BIGType::CUBE);
	cube.SetTexture(BITType::CONTAINER);
	//create skybox
	//-------------
	Skybox skybox(resMgr.LoadTexture(skyboxTexs, "skybox"));
	//draw as wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	windowMgr.Show();

	//create framebuffers
	//----------------
	FramebuffersManager DefaultSpace(windowMgr.GetWindow());
	DefaultSpace.CreateScreenQuad(1);
	FramebuffersManager PostProcSpace(windowMgr.GetWindow());
	PostProcSpace.CreateScreenQuad(1);

	//render loop
	//-----------
	while (!glfwWindowShouldClose(windowMgr.GetWindow()))
	{
		windowMgr.ProcessInput();

		//render
		//------
		//bind to framebuffer
		//-----------------------------------------------------------------------------------------------------------------
		DefaultSpace.Bind();
		glEnable(GL_DEPTH_TEST);

		//make sure we clear the framebuffer's content
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//set MVP Matrix
		auto model = glm::mat4(1.0f);
		auto view = camera.GetViewMatrix();
		UBO.BindPoint(BINDING_POINT_0);
		UBO.SetSubData(0, sizeof(glm::mat4), glm::value_ptr(view));
		auto [width, height] = GetFramebufferSize(windowMgr.GetWindow());
		auto projection = glm::perspective(glm::radians(camera.Zoom), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);
		UBO.SetSubData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(projection));

		defaultShader.Use().SetMat4("model", model);
		cube.Render(defaultShader);
		//skybox render
		glDepthFunc(GL_LEQUAL);
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		skybox.Render(skyboxShader, view, projection);
		glDepthFunc(GL_LESS);

		//bind back to default framebuffer
		//-----------------------------------------------------------------------------------------------------------------
		DefaultSpace.UnBind();
		glDisable(GL_DEPTH_TEST);
		//clear all relevant buffers
		glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		auto transform = glm::mat4(1.0f);
		DefaultSpace.Render(screenDefaultShader);

		windowMgr.UpData();
	}

	//cube.Delete();
	DefaultSpace.Delete();
	PostProcSpace.Delete();
	skybox.Delete();
	windowMgr.Delete();

	return 0;
}