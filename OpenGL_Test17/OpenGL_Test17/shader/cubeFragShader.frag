#version 330 core

uniform vec3 cubeColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

in  vec3 normal;
in  vec3 fragPos;
out vec4 fragColor;

void main()
{
    //ambient
    float ambientStrength = 0.2;
    vec3  ambient         = ambientStrength * lightColor;

    //diffuse
    vec3  norm     = normalize(normal);
    vec3  lightDir = normalize(lightPos - fragPos);
    float diff     = max(dot(norm, lightDir), 0.0f);
    vec3  diffuse  = diff * lightColor;

    //fragColor
    vec3  result = (ambient + diffuse) * cubeColor;
    fragColor = vec4(result, 1.0f);
}