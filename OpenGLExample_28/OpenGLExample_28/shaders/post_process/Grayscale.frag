#version 330 core

in  vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D screenTexture;
void main()
{
    vec3 col = texture(screenTexture, TexCoords).rgb;
    float average = 0.2126 * col.r + 0.7152 * col.g + 0.0722 * col.b;
    FragColor = vec4(average, average, average, 1.0);
}