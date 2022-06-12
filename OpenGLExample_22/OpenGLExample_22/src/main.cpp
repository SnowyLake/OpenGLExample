#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLCamera.h>
#include <GLShader.h>
#include "../include/CreateWindow.h"
#include "../include/Model.h"
#include "../include/Lamp.h"

#include<iostream>

//setting
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;

std::vector<float> pointLightVertices = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};
std::vector<glm::vec3> pointLightPositions = {
	glm::vec3(4.0f,  -15.0f,  1.5f),
	glm::vec3(-3.0f, -6.0f, 2.0f),
	glm::vec3(-4.0f, -13.0f, -2.0f),
	glm::vec3(7.0f,  -8.0f, -6.0f)
};//RIGHT HAND

int main()
{
	CreateWindow MainWindow(SCR_WIDTH, SCR_HEIGHT, "Model Loading Test", nullptr, nullptr, true);
	MainWindow.SetCallback();

	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	stbi_set_flip_vertically_on_load(false);

	//load resources
	std::cout << "Start load resources." << std::endl;

	std::cout << "Loading Model..." << std::endl;
	std::cout << "Loading Model Textures..." << std::endl;
	Model loadedModel("res/nanosuit/nanosuit.obj");
	std::cout << "Loaded Model Textures, Textures Number: " << loadedModel.texturesLoaded.size() << std::endl;

	std::cout << "Loaded Model." << std::endl;
	std::cout << "\tVertices Number: " << loadedModel.numVertices << std::endl;
	std::cout << "\tFaces Number: " << loadedModel.numFaces << std::endl;
	std::cout << "\tMeshes Number: " << loadedModel.meshes.size() << std::endl;

	std::cout << "Loading Lamps..." << std::endl;
	Lamp builtInLamps(pointLightVertices, pointLightPositions);
	std::cout << "Loaded Lamps." << std::endl;

	std::cout << "Loading shader..." << std::endl;
	GLShader modelShader("shader/model.vert", "shader/model.frag");
	GLShader lampShader("shader/lamp.vert", "shader/lamp.frag");
	
	std::cout << "Loaded shader." << std::endl;

	std::cout << "Resources loaded." << std::endl;
	
	glfwSetWindowPos(MainWindow.window, 600, 100);
	glfwShowWindow(MainWindow.window);

	while (!glfwWindowShouldClose(MainWindow.window))
	{
		MainWindow.SetPerFrameTimeLogic();
		MainWindow.ProcessInput();

		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		modelShader.use();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)MainWindow.GetScrWidth() / (float)MainWindow.GetScrHeight(), 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		modelShader.SetMat4("projection", projection);
		modelShader.SetMat4("view", view);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		modelShader.SetMat4("model", model);

		modelShader.SetFloat("material.shininess", 32.0f);
		loadedModel.Render(modelShader);

		builtInLamps.LightRenderConfigInit(modelShader, camera);
		builtInLamps.DirLightRenderConfig(modelShader);
		builtInLamps.PointLightRenderConfig(modelShader);
		builtInLamps.SpotLightRenderConfig(modelShader, camera);
		builtInLamps.RenderPointLights(lampShader, view, projection);

		glfwSwapBuffers(MainWindow.window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
#endif // !STB_IMAGE_IMPLEMENTATION