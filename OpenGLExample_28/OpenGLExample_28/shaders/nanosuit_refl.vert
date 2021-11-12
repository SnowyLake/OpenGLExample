#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 normal_matrix;

void main()
{
    Normal = mat3(normal_matrix) * aNormal;
    FragPos   = vec3(model * vec4(aPos, 1.0f));
    TexCoords = aTexCoords;    
    
    gl_Position = projection * view * model * vec4(aPos, 1.0);
} 