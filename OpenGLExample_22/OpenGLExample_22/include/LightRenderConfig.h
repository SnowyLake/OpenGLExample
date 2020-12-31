#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<GLCamera.h>
#include<GLShader.h>

#include<vector>
#include<string>

extern std::vector<float> pointLightVertices;
extern std::vector<glm::vec3> pointLightPositions;

void LightRenderConfigInit(GLShader& shader, const GLCamera& camera);
void DirLightRenderConfig(GLShader& shader);
void PointLightRenderConfig(GLShader& shader, const std::vector<glm::vec3>& pointLightPositions);
void SpotLightRenderConfig(GLShader& shader, const GLCamera& camera);