#version 330 core
out vec4 FragColor;

struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    sampler2D texture_normal1;
};

in vec2 TexCoords;

uniform Material material;

void main()
{    
    vec4 diffuse = texture(material.texture_diffuse1, TexCoords);
    vec4 specular = texture(material.texture_specular1, TexCoords);
    vec4 normal = texture(material.texture_normal1, TexCoords);
    FragColor = diffuse;
}