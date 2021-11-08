#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoords;
uniform mat4 transform;

void main()
{
    TexCoords = aTexCoord;
    gl_Position = transform * vec4(aPos.x, aPos.y, 0.0, 1.0);
}