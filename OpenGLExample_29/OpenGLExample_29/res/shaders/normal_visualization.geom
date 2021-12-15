#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT 
{
    vec3 normal;
}gs_in[];

layout (std140) uniform Matrices
{
    mat4 view;
    mat4 projection;
};
uniform mat4 model;
uniform mat3 normalMatrix;

const float MAGNITUDE = 0.2;
void GenLine(int idx)
{
    gl_Position = projection * view * model * gl_in[idx].gl_Position;
    EmitVertex();
    vec4 viewSpacePos = view * model * gl_in[idx].gl_Position;
    vec4 viewSpaceNormal = vec4(normalize(normalMatrix * gs_in[idx].normal) * MAGNITUDE, 0.0);
    gl_Position = projection * (viewSpacePos + viewSpaceNormal);
    EmitVertex();
    EndPrimitive();
}

void main()
{
    GenLine(0);
    GenLine(1);
    GenLine(1);
}