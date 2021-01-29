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
	WindowManager windowMgr(SCR_WIDTH, SCR_HEIGHT, "Depth Testing", nullptr, nullptr, true);
	windowMgr.SetCallback();

	//configure global OpenGL state
	//-----------------------------
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	std::vector<BuiltInObject> cubes = 
	{
		BuiltInObject(BIOType::OBJ_CUBE),
		BuiltInObject(BIOType::OBJ_CUBE)
	};
	BuiltInObject plane(BIOType::OBJ_PLANE);

	GLShader shader("shader/depth_testing.vert", "shader/depth_testing.frag");

	shader.use();
	shader.SetInt("texture1", 0);

	glfwSetWindowPos(windowMgr.window, 300, 100);
	glfwShowWindow(windowMgr.window);

	while(!glfwWindowShouldClose(windowMgr.window))
	{
		windowMgr.SetPerFrameTimeLogic();
		windowMgr.ProcessInput();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = camera.GetViewMatrix();

		int width, height;
		glfwGetFramebufferSize(windowMgr.window, &width, &height);		//When the window scale is changed, the render scale stays the same
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);

		//first cube
		model = glm::translate(model, glm::vec3(-1.0f, -1.001f, -1.0f));
		cubes.at(0).BuiltInObjRender(shader, model, view, projection);

		//secend cube
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, -1.0001f, 0.0f));
		cubes.at(1).BuiltInObjRender(shader, model, view, projection);

		//plane
		model = glm::mat4(1.0f);
		plane.BuiltInObjRender(shader, model, view, projection);

		glfwSwapBuffers(windowMgr.window);
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

