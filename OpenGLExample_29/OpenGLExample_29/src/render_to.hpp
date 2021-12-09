#pragma once

#include <concepts>

#include "shader.h"
#include "model.h"
#include "skybox.h"
#include "geometry.h"
#include "frame_buffer.h"

template<typename T, typename S = Shader>
concept Renderable = requires(T t, S s) { t.Render(s); };

template<Renderable T>
struct RenderTo
{
	RenderTo(T& t) :object(t) {}

	friend void operator>>(Shader& shader, RenderTo rt)
	{
		rt.object.Render(shader);
	}

private:
	T& object;
};