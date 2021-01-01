#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<GLCamera.h>
#include<GLShader.h>

#include<vector>
#include<string>

extern float pointLightVertices[];
extern std::vector<glm::vec3> pointLightPositions;

void LightRenderConfigInit(GLShader& shader, const GLCamera& camera);
void DirLightRenderConfig(GLShader& shader);
void PointLightRenderConfig(GLShader& shader, const std::vector<glm::vec3>& pointLightPositions);
void SpotLightRenderConfig(GLShader& shader, const GLCamera& camera);

extern unsigned int lampVAO;
extern unsigned int lampVBO;

void SetLampsVAO();
void RenderPointLights(GLShader& shader, const glm::mat4 view, const glm::mat4 projection);