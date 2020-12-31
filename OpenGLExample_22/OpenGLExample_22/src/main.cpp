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
#include "../include/LightRenderConfig.h"

#include<iostream>

//setting
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;

int main()
{
	CreateWindow MainWindow(SCR_WIDTH, SCR_HEIGHT, "Model Loading Test", nullptr, nullptr, true);
	MainWindow.SetCallback();

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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

	std::cout << "Loading shader..." << std::endl;
	GLShader shader("shader/model.vert", "shader/model.frag");
	std::cout << "Loaded shader." << std::endl;

	std::cout << "Resources loaded." << std::endl;
	
	glfwSetWindowPos(MainWindow.window, 600, 100);
	glfwShowWindow(MainWindow.window);

	while (!glfwWindowShouldClose(MainWindow.window))
	{
		MainWindow.SetPerFrameTimeLogic();
		MainWindow.ProcessInput();

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		shader.use();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)MainWindow.GetScrWidth() / (float)MainWindow.GetScrHeight(), 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		shader.SetMat4("projection", projection);
		shader.SetMat4("view", view);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		shader.SetMat4("model", model);

		shader.SetFloat("material.shininess", 32.0f);
		
		//shader.SetVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		//shader.SetVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		//shader.SetVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		//shader.SetVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
		//shader.SetVec3("pointLights[0].position", pointLightPositions[0]);
		//shader.SetVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		//shader.SetVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		//shader.SetVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		//shader.SetFloat("pointLights[0].constant", 1.0f);
		//shader.SetFloat("pointLights[0].linear", 0.09);
		//shader.SetFloat("pointLights[0].quadratic", 0.032);
		//shader.SetVec3("spotLight.position", camera.Position);
		//shader.SetVec3("spotLight.direction", camera.Front);
		//shader.SetVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		//shader.SetVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		//shader.SetVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		//shader.SetFloat("spotLight.constant", 1.0f);
		//shader.SetFloat("spotLight.linear", 0.09);
		//shader.SetFloat("spotLight.quadratic", 0.032);
		//shader.SetFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		//shader.SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

		LightRenderConfigInit(shader, camera);
		DirLightRenderConfig(shader);
		PointLightRenderConfig(shader, pointLightPositions);
		SpotLightRenderConfig(shader, camera);

		loadedModel.Render(shader);

		glfwSwapBuffers(MainWindow.window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
#endif // !STB_IMAGE_IMPLEMENTATION