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

#include<iostream>

//setting
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;

int main()
{
	CreateWindow MainWindow(SCR_WIDTH, SCR_HEIGHT, "Model Loading Test", NULL, NULL, true);
	MainWindow.SetCallback();

	stbi_set_flip_vertically_on_load(false);

	glEnable(GL_DEPTH_TEST);

	GLShader shader("shader/model.vert", "shader/model.frag");
	Model loadedModel("res/nanosuit/nanosuit.obj");

	while (!glfwWindowShouldClose(MainWindow.window))
	{
		MainWindow.SetPerFrameTimeLogic();
		MainWindow.ProcessInput();
		//std::cout << "proc OK" << std::endl;

		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)MainWindow.GetScrWidth() / (float)MainWindow.GetScrHeight(), 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		shader.SetMat4("projection", projection);
		shader.SetMat4("view", view);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		shader.SetMat4("model", model);
		loadedModel.Draw(shader);

		glfwSwapBuffers(MainWindow.window);
		glfwPollEvents();
		//std::cout << "poll" << std::endl;
	}
	glfwTerminate();
	return 0;
}
