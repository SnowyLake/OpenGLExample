#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    sampler2D texture_normal1;
    sampler2D texture_reflection1;
    float shininess;
};

uniform Material material;
uniform vec3 cameraPos;
uniform samplerCube skyboxTex;

void main()
{
    vec3 I = normalize(FragPos - cameraPos);
    vec3 normal = normalize(Normal);
    vec3 R = reflect(I, normal);

    vec3 reflectMap = vec3(texture(material.texture_reflection1, TexCoords));
    vec3 reflection = vec3(texture(skyboxTex, R).rgb) * reflectMap;

    vec3 diffuse = vec3(texture(material.texture_diffuse1, TexCoords));

    FragColor = vec4(diffuse + reflection, 1.0f);
}
