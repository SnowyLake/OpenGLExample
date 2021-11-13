#version 330 core

in  vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D screenTex;
void main()
{
    FragColor = vec4(vec3(texture(screenTex, TexCoords)), 1.0);
}