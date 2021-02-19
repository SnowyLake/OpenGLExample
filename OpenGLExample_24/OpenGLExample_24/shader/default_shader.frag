#version 330 core
varying vec2 TexCoords;

uniform sampler2D texture1;

void main()
{
    gl_FragColor = texture(texture1, TexCoords);
}
