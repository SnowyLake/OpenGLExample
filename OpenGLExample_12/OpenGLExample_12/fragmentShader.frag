#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

//texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
//mixvalue
uniform float mixValue;

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue)/*vec4(ourColor, 1.0)*/;
}