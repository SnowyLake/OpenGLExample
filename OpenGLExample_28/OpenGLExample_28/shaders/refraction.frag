#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skyboxTex;

void main()
{
    float ratio = 1.00 / 1.52;  //玻璃折射率
    vec3 I = normalize(Position - cameraPos);   //观察方向向量I
    vec3 R = refract(I, normalize(Normal), ratio);     //反射向量R
    FragColor = vec4(texture(skyboxTex, R).rgb, 1.0);
}