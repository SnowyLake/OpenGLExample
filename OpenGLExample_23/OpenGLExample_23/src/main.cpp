#define STB_IMAGE_IMPLEMENTATION

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
	glDepthFunc(GL_ALWAYS);

	GLShader shader("shader/DepthTesting.vert", "shader/DepthTesting.frag");
}

