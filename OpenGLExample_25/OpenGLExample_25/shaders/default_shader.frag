#version 330 core
out vec4 FragColor;
varying vec2 TexCoords;

uniform sampler2D texture1;

void main()
{
    vec4 TexColor = texture(texture1, TexCoords);
    if(TexColor.a < 0.1)
        discard;
    FragColor = TexColor;
}
