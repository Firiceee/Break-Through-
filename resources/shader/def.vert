#version 330 core

layout (location = 0) in vec4 Vertex;

uniform mat4 projection, model;
out vec2 texturePos;

void main()
{
    texturePos = Vertex.zw;
    gl_Position = projection * model * vec4(Vertex.xy, 0, 1.f);
}