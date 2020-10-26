#version 330 core
uniform vec3 cubeColor;
uniform vec3 lightColor;

in  vec3 Normal;
in  vec3 FragPos;
in  vec3 LightPos;

out vec4 FragColor;

void main()
{
    //ambient
    float ambientStrength = 0.1;
    vec3  ambient         = ambientStrength * lightColor;

    //diffuse
    vec3  norm     = normalize(Normal);
    vec3  lightDir = normalize(LightPos - FragPos);
    float diff     = max(dot(norm, lightDir), 0.0f);
    vec3  diffuse  = diff * lightColor;

    //specular
    float  specularStrength  = 0.5f;
    vec3   viewDir    = normalize(-FragPos);
    vec3   reflectDir = reflect(-lightDir, norm);
    float  spec       = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3   specular   = specularStrength * spec * lightColor; 

    //fragColor
    vec3  result = (ambient + diffuse + specular) * cubeColor;
    FragColor = vec4(result, 1.0f);
}