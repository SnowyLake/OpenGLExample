#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <gl_camera.h>
#include <gl_shader.h>
#include "../include/create_window.h"
#include "../include/builtin_obj.h"

//setting
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;

int main()
{
	CreateWindow MainWindow(SCR_WIDTH, SCR_HEIGHT, "Depth Testing", nullptr, nullptr, true);
	MainWindow.SetCallback();

	//configure global OpenGL state
	//-----------------------------
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	std::vector<BuiltInObject> cubes = 
	{
		BuiltInObject(BuiltInObjectType::OBJ_CUBE),
		BuiltInObject(BuiltInObjectType::OBJ_CUBE)
	};
	BuiltInObject plane(BuiltInObjectType::OBJ_PLANE);

	GLShader shader("shader/depth_testing.vert", "shader/depth_testing.frag");

	shader.use();
	shader.SetInt("texture1", 0);

	glfwSetWindowPos(MainWindow.window, 600, 100);
	glfwShowWindow(MainWindow.window);

	while(!glfwWindowShouldClose(MainWindow.window))
	{
		MainWindow.SetPerFrameTimeLogic();
		MainWindow.ProcessInput();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = camera.GetViewMatrix();

		int width, height;
		glfwGetFramebufferSize(MainWindow.window, &width, &height);		//When the window scale is changed, the render scale stays the same
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);

		//first cube
		model = glm::translate(model, glm::vec3(-1.0f, -1.0f, -1.0f));
		cubes.at(0).BuiltInObjRender(shader, model, view, projection);

		//secend cube
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, -1.0f, 0.0f));
		cubes.at(1).BuiltInObjRender(shader, model, view, projection);

		//plane
		model = glm::mat4(1.0f);
		plane.BuiltInObjRender(shader, model, view, projection);

		glfwSwapBuffers(MainWindow.window);
		glfwPollEvents();
	}

	for(auto& i : cubes)
	{
		i.DeleteVAO();
		i.DeleteBuffers();
	}
	plane.DeleteVAO();
	plane.DeleteBuffers();

	glfwTerminate();
	return 0;
}

