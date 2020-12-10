#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include<GLShader.h>

#include"CreateWindow.h"
#include"ResLoad.h"

#include <iostream>


//lighting
glm::vec3 lightPos = glm::vec3(0.7f, -0.7f, 1.4f);

int main()
{
	GLFWwindow* window = CreateWindow(SCR_WIDTH, SCR_HEIGHT, "LightTest");

	//configure global opengl state
	glEnable(GL_DEPTH_TEST);

	//build shader
	GLShader cubeShader("shader/cubeVertShader.vert", "shader/cubeFragShader.frag");
	GLShader lightShader("shader/lightVertShader.vert", "shader/lightFragShader.frag");

	//set vertex data and configure vertex attributes
	float vertices[] = {
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
	// positions all containers
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	// positions of the point lights
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	//configure the cube's VAO and VBO
	unsigned int cubeVAO, VBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//Normal Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//Texture coords Attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//configure light's VAO
	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//load textures
	unsigned int diffuseMap = LoadTexture("map/diffuseMap.png");
	unsigned int specularMap = LoadTexture("map/specularMap.png");
	//unsigned int specularMap = LoadTexture("Map/specularMap_color.png");
	cubeShader.use();
	cubeShader.SetInt("material.difffuse", 0);
	cubeShader.SetInt("material.specular", 1);

	//render loop
	//-----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastTime;
		lastTime = currentFrame;

		// input
		// -----
		ProcessInput(window);

		// render
		// ------
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// be sure to activate shader when setting uniforms/drawing objects
		cubeShader.use();
		cubeShader.SetVec3("viewPos", camera.Position);
		cubeShader.SetFloat("material.shininess", 32.0f);

		// directional light
		cubeShader.SetVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		cubeShader.SetVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		cubeShader.SetVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		cubeShader.SetVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
		// point light 1
		cubeShader.SetVec3("pointLights[0].position", pointLightPositions[0]);
		cubeShader.SetVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		cubeShader.SetVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		cubeShader.SetVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		cubeShader.SetFloat("pointLights[0].constant", 1.0f);
		cubeShader.SetFloat("pointLights[0].linear", 0.09);
		cubeShader.SetFloat("pointLights[0].quadratic", 0.032);
		// point light 2
		cubeShader.SetVec3("pointLights[1].position", pointLightPositions[1]);
		cubeShader.SetVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		cubeShader.SetVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		cubeShader.SetVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		cubeShader.SetFloat("pointLights[1].constant", 1.0f);
		cubeShader.SetFloat("pointLights[1].linear", 0.09);
		cubeShader.SetFloat("pointLights[1].quadratic", 0.032);
		// point light 3
		cubeShader.SetVec3("pointLights[2].position", pointLightPositions[2]);
		cubeShader.SetVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		cubeShader.SetVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
		cubeShader.SetVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		cubeShader.SetFloat("pointLights[2].constant", 1.0f);
		cubeShader.SetFloat("pointLights[2].linear", 0.09);
		cubeShader.SetFloat("pointLights[2].quadratic", 0.032);
		// point light 4
		cubeShader.SetVec3("pointLights[3].position", pointLightPositions[3]);
		cubeShader.SetVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		cubeShader.SetVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		cubeShader.SetVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		cubeShader.SetFloat("pointLights[3].constant", 1.0f);
		cubeShader.SetFloat("pointLights[3].linear", 0.09);
		cubeShader.SetFloat("pointLights[3].quadratic", 0.032);
		// spotLight
		cubeShader.SetVec3("spotLight.position", camera.Position);
		cubeShader.SetVec3("spotLight.direction", camera.Front);
		cubeShader.SetVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		cubeShader.SetVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		cubeShader.SetVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		cubeShader.SetFloat("spotLight.constant", 1.0f);
		cubeShader.SetFloat("spotLight.linear", 0.09);
		cubeShader.SetFloat("spotLight.quadratic", 0.032);
		cubeShader.SetFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		cubeShader.SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		cubeShader.SetMat4("projection", projection);
		cubeShader.SetMat4("view", view);
		//world transformation
		glm::mat4 model = glm::mat4(1.0f);
		cubeShader.SetMat4("model", model);

		//bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		//bind specular map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		// render containers
		glBindVertexArray(cubeVAO);
		for (size_t i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			cubeShader.SetMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//draw the lamp object
		lightShader.use();
		lightShader.SetMat4("view", view);
		lightShader.SetMat4("projection", projection);
		//lightShader.SetVec3("lightColor", lightColor);

		glBindVertexArray(lightVAO);
		for (size_t i = 0; i < 4; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2));
			lightShader.SetMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}
