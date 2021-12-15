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
#include "to_render.hpp"

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

	//resource mananger init
	auto& ResMgr = ResourceMananger::GetInstance();

	//shaders
	//-------
	ResMgr.LoadShader("res/builtin/shaders/skybox.vert",
					  "res/builtin/shaders/skybox.frag",
					  nullptr,
					  "skybox");
	ResMgr.LoadShader(PostProcessShaders::DefaultVert,
					  PostProcessShaders::DefaultFrag,
					  nullptr,
					  "postproc");
	ResMgr.LoadShader("res/shaders/model_default.vert",
					  "res/shaders/model_default.frag",
					  nullptr,
					  "model_default");
	ResMgr.LoadShader("res/shaders/gs_test.vert",
					  "res/shaders/gs_test.frag",
					  "res/shaders/gs_test.geom",
					  "geometry_test");
	ResMgr.LoadShader("res/shaders/model_explode.vert",
					  "res/shaders/model_explode.frag",
					  "res/shaders/model_explode.geom",
					  "model_explode");
	ResMgr.LoadShader("res/shaders/normal_visualization.vert",
					  "res/shaders/normal_visualization.frag",
					  "res/shaders/normal_visualization.geom",
					  "normal_visualization");

	//shader config
	ResMgr.GetShader("skybox").Use().SetInt("skyboxTex", 0);
	ResMgr.GetShader("postproc").Use().SetInt("screenTex", 0);
	UniformBlockBindPoint(ResMgr.GetShader("model_default"), "Matrices", BINDING_POINT_0);

	//create scene objects
	Geometry points(pointsVertices, {2u,3u});
	Model nanosuit("res/builtin/model/nanosuit/nanosuit.obj");
	Skybox skybox(ResMgr.LoadTexture(paths, "skybox"));

	//uniform buffer
	UniformBuffer UBO(2 * sizeof(glm::mat4));
	UBO.BindPoint(BINDING_POINT_0);
	
	//draw as wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	window.Show(100, 100);

	//create framebuffers
	FrameBuffer defaultSpace(window);
	defaultSpace.CreateScreenQuad(1);

	//render loop
	//-----------
	while (!glfwWindowShouldClose(window.Get()))
	{
		window.ProcessInput();

		//defaultSpace
		//----------------------------------------------------------------
		/*bind  */ defaultSpace.Bind().Update(window);

		//make sure we clear the framebuffer's content
		ClearBuffer(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//MVP
		auto model = glm::mat4(1.0f);
		auto view = camera.GetViewMatrix();
		auto [_width, _height] = window.GetSize();
		auto projection = glm::perspective(glm::radians(camera.Zoom), static_cast<float>(_width) / static_cast<float>(_height), 0.1f, 100.0f);
		//uniform update
		UBO.Bind()
			.SetSubData(0, sizeof(glm::mat4), glm::value_ptr(view))
			.SetSubData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(projection));
		
		//render
		//points.Render(geomTestShader, false, GL_POINTS);

		ResMgr.GetShader("model_default").Use()
			.SetMat4("model", model) >> ToRender(nanosuit);

		ResMgr.GetShader("normal_visualization").Use()
			.SetMat4("model", model)
			.SetMat3("normalMatrix", glm::mat3(glm::transpose(glm::inverse(view * model))))
			>> ToRender(nanosuit);

		/*ResMgr.GetShader("model_explode").Use()
			.SetMat4("model", model)
			.SetMat3("normalMatrix", glm::mat3(glm::transpose(glm::inverse(view * model))))
			.SetFloat("time", static_cast<float>(glfwGetTime()))
			>> ToRender(nanosuit);*/
		
		//skybox
		ResMgr.GetShader("skybox").Use()
			.SetMat4("view", glm::mat4(glm::mat3(view)))
			.SetMat4("projection", projection)
			>> ToRender(skybox);

		/*unbind*/ defaultSpace.UnBind();
		//----------------------------------------------------------------
		//clear all relevant buffers
		ClearBuffer();
		//framebuffer render
		ResMgr.GetShader("postproc").Use() >> ToRender(defaultSpace);
		window.UpData();
	}
	points.Destory();
	skybox.Destory();
	defaultSpace.Destory();
	window.Destory();

	return 0;
}