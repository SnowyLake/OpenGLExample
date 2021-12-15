#pragma once
#include <concepts>

#include "shader.h"
#include "model.h"
#include "skybox.h"
#include "geometry.h"
#include "frame_buffer.h"

template<typename T, typename S = Shader>
concept Renderable = requires(T t, S s)
{ 
	t.Render(s);
};

template<Renderable T>
struct ToRender
{
	ToRender(T& t) :object(t) {}
	friend void operator>>(Shader& shader, ToRender tr)
	{
		tr.object.Render(shader);
	}

	~ToRender() = default;
	ToRender(const ToRender&) = delete;
	ToRender(ToRender&&) = delete;
	ToRender& operator=(const ToRender&) = delete;
	ToRender& operator=(ToRender&&) = delete;
private:
	T& object;
};