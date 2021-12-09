#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <string_view>
#include <format>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



using uint = unsigned int;
class Shader
{
public:
	Shader(std::string_view name);
	~Shader() = default;
	Shader(const Shader&) = default;
	Shader(Shader&&) noexcept = default;
	Shader& operator=(const Shader&) = default;
	Shader& operator=(Shader&&) noexcept = default;

	void Compile(const char* vertexPath, const char* fragmentPath, const char* geometryPath);
	uint GetID() const;
	std::string& GetName();

	Shader& Use();
	Shader& SetInt	 (const char* name, int   value);
	Shader& SetBool	 (const char* name, bool  value);
	Shader& SetFloat (const char* name, float value);
	Shader& SetVec2  (const char* name, float x, float y);
	Shader& SetVec2  (const char* name, const glm::vec2& value);
	Shader& SetVec3  (const char* name, float x, float y, float z);
	Shader& SetVec3  (const char* name, const glm::vec3& value);
	Shader& SetVec4  (const char* name, float x, float y, float z, float w);
	Shader& SetVec4  (const char* name, const glm::vec4& value);
	Shader& SetMat2  (const char* name, const glm::mat2& value);
	Shader& SetMat3  (const char* name, const glm::mat3& value);
	Shader& SetMat4  (const char* name, const glm::mat4& value);

private:
	uint m_ID;
	std::string m_name;
	void CheckCompileErrors(uint shader, std::string_view type);
};

//#include "geometry.h"
//#include "model.h"
//#include "skybox.h"
//#include "frame_buffer.h"

//template<typename T>
//concept Renderable = 
//std::is_same_v<T, Geometry> ||
//std::is_same_v<T, Model>	||
//std::is_same_v<T, Skybox>	||
//std::is_same_v<T, FrameBuffer>;
// 
//template<Renderable T>
//inline Shader& ToRender(T& obj)
//{
//	obj.Render(*this);
//}
