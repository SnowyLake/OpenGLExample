#version 330 core

in  vec3 TexCoords;
out vec4 FragColor;

uniform samplerCube skyboxTex;

void main()
{
    FragColor = texture(skyboxTex, TexCoords);
}
