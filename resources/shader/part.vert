#version 330 core

layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 texturePos;
out vec4 particleColor;

uniform mat4 projection;
uniform mat4 model;
uniform vec4 color;

void main()
{
    texturePos = vertex.zw;
    particleColor = color;
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}