#version 330 core

out vec4 FragColor;
uniform vec3 cubeColor;
uniform vec3 lightColor;

void main()
{
    FragColor = vec4(lightColor * cubeColor, 1.0f);
}
