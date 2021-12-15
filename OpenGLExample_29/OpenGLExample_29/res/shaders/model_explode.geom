#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 6) out;

out vec2 texCoords;

in VS_OUT
{
    vec2 texCoords;
    vec3 normal;
}gs_in[];

layout (std140) uniform Matrices
{
    mat4 view;
    mat4 projection;
};
uniform mat4 model;
uniform mat3 normalMatrix;
uniform float time;

vec4 Explode(int index, vec3 normal)
{
    float magnitude = 2.0;
    vec4 viewSpacePos = view * model * gl_in[index].gl_Position;
    vec4 viewSpaceNormal = vec4(normal * ((sin(time) + 1.0) / 2.0) * magnitude, 0.0);
    return projection * (viewSpacePos + viewSpaceNormal);
}
vec3 GetViewSpaceNormal(mat3 normalMatrix)
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[0].gl_Position) - vec3(gl_in[2].gl_Position);
    return normalize(normalMatrix * cross(a, b));
}

void main()
{
    vec3 normal = GetViewSpaceNormal(normalMatrix);

    gl_Position = Explode(0, normal);
    texCoords = gs_in[0].texCoords;
    EmitVertex();

    gl_Position = Explode(1, normal);
    texCoords = gs_in[1].texCoords;
    EmitVertex();

    gl_Position = Explode(2, normal);
    texCoords = gs_in[2].texCoords;
    EmitVertex();

    EndPrimitive();
}