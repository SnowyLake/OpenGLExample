#include <map>
#include <vector>
#include <string>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <gl_camera.h>
#include <gl_shader.h>

#include "../include/utility.hpp"
#include "../include/model.h"
#include "../include/builtin_obj.h"
#include "../include/window_manager.h"
#include "../include/skybox_manager.h"
#include "../include/framebuffers_manager.h"
#include "../include/uniform_buffer_manager.h"
#include "../shaders/post_process/post_process_shaders.h"

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "assimp-vc143-mt.lib")

//setting
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;
const std::string EXAMPLE_NAME = "UBO";
const unsigned int BINDING_POINT_0 = 0;

//camera
extern GLCamera camera(glm::vec3(0.0f, 0.0f, 10.0f));

//skybox
std::vector<std::string> faces = {
	"res/skybox/right.jpg",
	"res/skybox/left.jpg",
	"res/skybox/top.jpg",
	"res/skybox/bottom.jpg",
	"res/skybox/front.jpg",
	"res/skybox/back.jpg"
};

int main()
{
	//create window
	WindowManager windowMgr(SCR_WIDTH, SCR_HEIGHT, EXAMPLE_NAME, nullptr, nullptr, true);
	windowMgr.SetCallback();

	//create framebuffers
	//----------------
	FramebuffersManager FBMgr(windowMgr.window);
	FBMgr.CreateScreenQuad(1);

	//configure global OpenGL state
	//-----------------------------
	glEnable(GL_DEPTH_TEST);

	//shaders
	//-------
	//GLShader defaultShader("shaders/default.vert", "shaders/default.frag");
	std::map<std::string, GLShader> shaders = {
		{"red",		GLShader("shaders/default.vert", "shaders/red.frag")	},
		{"green",	GLShader("shaders/default.vert", "shaders/green.frag")	},
		{"blue",	GLShader("shaders/default.vert", "shaders/blue.frag")	},
		{"yellow",	GLShader("shaders/default.vert", "shaders/yellow.frag")	}
	};
	
	GLShader skyboxShader("shaders/skybox.vert", "shaders/skybox.frag");
	GLShader screenShader(PostProcessShaders::DefaultVert, PostProcessShaders::DefaultFrag);
	
	//shader config
	//-------------
	/*defaultShader.Use();
	defaultShader.SetInt("texture1", 0);*/
	for (auto& i : shaders)
	{
		UniformBlockBind(i.second, "Matrices", BINDING_POINT_0);
	}

	skyboxShader.Use()
		.SetInt("skyboxTex", 0);
	screenShader.Use()
		.SetInt("screenTex", 0);

	//create UBO
	UniformBufferManager UBO(2 * sizeof(glm::mat4));
	UBO.BindPoint(BINDING_POINT_0);
	auto [_width, _height] = GetFramebufferSize(windowMgr.window);
	auto projection = glm::perspective(glm::radians(camera.Zoom), static_cast<float>(_width) / static_cast<float>(_height), 0.1f, 100.0f);
	UBO.SetSubData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(projection));
	

	//scene objects
	//-------------
	BuiltInObject cube(BIOType::OBJ_CUBE);

	//create skybox
	//-------------
	SkyboxManager skyboxMgr(faces);

	//draw as wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	windowMgr.Show(300, 100);

	//render loop
	//-----------
	while (!glfwWindowShouldClose(windowMgr.window))
	{
		windowMgr.ProcessInput();

		//render
		//------
		//bind to framebuffer
		//-----------------------------------------------------------------------------------------------------------------
		FBMgr.Bind();
		glEnable(GL_DEPTH_TEST);

		//make sure we clear the framebuffer's content
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//set MVP Matrix
		auto model = glm::mat4(1.0f);
		auto view = camera.GetViewMatrix();
		UBO.SetSubData(0, sizeof(glm::mat4), glm::value_ptr(view));

		//draw four cubes
		//red
		shaders.at("red").Use();
		model = glm::translate(model, glm::vec3(-0.75f, 0.75f, 0.0f));	//move top-left
		cube.BuiltInObjRender(shaders.at("red"), model, true);
		//green
		shaders.at("green").Use();
		model = glm::translate(model, glm::vec3(0.75f, 0.75f, 0.0f));	//move top-left
		cube.BuiltInObjRender(shaders.at("green"), model, true);
		//blue
		shaders.at("blue").Use();
		model = glm::translate(model, glm::vec3(-0.75f, -0.75f, 0.0f));	//move top-left
		cube.BuiltInObjRender(shaders.at("blue"), model, true);
		//yellow
		shaders.at("yellow").Use();
		model = glm::translate(model, glm::vec3(0.75f, -0.75f, 0.0f));	//move top-left
		cube.BuiltInObjRender(shaders.at("yellow"), model, true);
		
		//glEnable(GL_CULL_FACE);     //open Face culling
		//defaultShader.Use();
		//cube.BuiltInObjRender(defaultShader, model, view, projection, true);
		//glDisable(GL_CULL_FACE);    //close Face culling

		//skybox render
		glDepthFunc(GL_LEQUAL);
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		skyboxMgr.Rneder(skyboxShader, view, projection);
		glDepthFunc(GL_LESS);

		//bind back to default framebuffer
		//-----------------------------------------------------------------------------------------------------------------
		FBMgr.UnBind();
		glDisable(GL_DEPTH_TEST);


		//clear all relevant buffers
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		auto transform = glm::mat4(1.0f);
		FBMgr.Render(screenShader, 1, transform);

		glfwSwapBuffers(windowMgr.window);
		glfwPollEvents();
	}

	cube.Delete();
	FBMgr.Delete();
	skyboxMgr.Delete();

	glfwTerminate();
	return 0;
}

