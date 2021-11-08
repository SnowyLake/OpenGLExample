#version 330 core

in  vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D screenTexture;

const float offsetVal = 1.0 / 300.0;
void main()
{
    vec2 offsets[9] = vec2[](
        vec2(-offsetVal,  offsetVal), // 左上
        vec2( 0.0,        offsetVal), // 上
        vec2( offsetVal,  offsetVal), // 右上
        vec2(-offsetVal,  0.0   ),    // 左
        vec2( 0.0,        0.0   ),    // 中
        vec2( offsetVal,  0.0   ),    // 右
        vec2(-offsetVal, -offsetVal), // 左下
        vec2( 0.0,       -offsetVal), // 下
        vec2( offsetVal, -offsetVal)  // 右下
    );
    float kernel[9] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
    );
    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
    {
        col += sampleTex[i] * kernel[i];
    }
    FragColor = vec4(col, 1.0);
}