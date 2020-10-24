#version 330 core

uniform vec3 cubeColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in  vec3 normal;
in  vec3 fragPos;
out vec4 fragColor;

void main()
{
    //ambient
    float ambientStrength = 0.1;
    vec3  ambient         = ambientStrength * lightColor;

    //diffuse
    vec3  norm     = normalize(normal);
    vec3  lightDir = normalize(lightPos - fragPos);
    float diff     = max(dot(norm, lightDir), 0.0f);
    vec3  diffuse  = diff * lightColor;

    //specular
    float  specularStrength  = 0.1f;
    vec3   viewDir    = normalize(viewPos - fragPos);
    vec3   reflectDir = reflect(-lightPos, norm);
    float  spec       = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3   specular   = specularStrength * spec * lightColor; 

    //fragColor
    vec3  result = (ambient + diffuse + specular) * cubeColor;
    fragColor = vec4(result, 1.0f);
}