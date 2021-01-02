#include "..\include\Lamp.h"

//-----------------------public-------------------------
Lamp::Lamp(std::vector<float> pointLightVertices, std::vector<glm::vec3> pointLightPositions)
{
	this->pointLightVertices = pointLightVertices;
	this->pointLightPositions = pointLightPositions;

	SetLampsVAO();
}
Lamp::~Lamp() { }

//set basic uniform of render
void Lamp::LightRenderConfigInit(GLShader& shader, const GLCamera& camera)
{
	shader.SetVec3("viewPos", camera.Position);
}

//set directional light uniform
void Lamp::DirLightRenderConfig(GLShader& shader)
{
	shader.SetVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	shader.SetVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	shader.SetVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	shader.SetVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
}

//set point lights uniform
void Lamp::PointLightRenderConfig(GLShader& shader)
{
	for (size_t i = 0; i < pointLightPositions.size(); i++)
	{
		shader.SetVec3("pointLights[" + std::to_string(i) + "].position", pointLightPositions[i]);
		shader.SetVec3("pointLights[" + std::to_string(i) + "].ambient", 0.5f, 0.5f, 0.5f);
		shader.SetVec3("pointLights[" + std::to_string(i) + "].diffuse", 0.8f, 0.8f, 0.8f);
		shader.SetVec3("pointLights[" + std::to_string(i) + "].specular", 1.0f, 1.0f, 1.0f);
		shader.SetFloat("pointLights[" + std::to_string(i) + "].constant", 1.0f);
		shader.SetFloat("pointLights[" + std::to_string(i) + "].linear", 0.09f);
		shader.SetFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.032f);
	}
}

//set spotlight uniform
void Lamp::SpotLightRenderConfig(GLShader& shader, const GLCamera& camera)
{
	shader.SetVec3("spotLight.position", camera.Position);
	shader.SetVec3("spotLight.direction", camera.Front);
	shader.SetVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	shader.SetVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	shader.SetVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	shader.SetFloat("spotLight.constant", 1.0f);
	shader.SetFloat("spotLight.linear", 0.014f);
	shader.SetFloat("spotLight.quadratic", 0.0007f);
	shader.SetFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	shader.SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
}

//render lights
void Lamp::RenderPointLights(GLShader& shader, const glm::mat4 view, const glm::mat4 projection)
{
	shader.use();
	shader.SetMat4("projection", projection);
	shader.SetMat4("view", view);

	glm::mat4 model;
	glBindVertexArray(lampVAO);
	for (size_t i = 0; i < pointLightPositions.size(); i++)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, pointLightPositions[i]);
		model = glm::scale(model, glm::vec3(1.0));
		shader.SetMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glBindVertexArray(0);
}

//-------------------------private-----------------------------
//set lamps VAO
void Lamp::SetLampsVAO()
{
	glGenVertexArrays(1, &lampVAO);
	glGenBuffers(1, &lampVBO);

	glBindVertexArray(lampVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lampVBO);
	glBufferData(GL_ARRAY_BUFFER, pointLightVertices.size() * sizeof(float), &pointLightVertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}


