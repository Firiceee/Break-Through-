#version 330 core

in vec2 texturePos;
in vec4 particleColor;

out vec4 ourColor;

uniform sampler2D tex;

void main()
{
    ourColor = particleColor * texture(tex, texturePos);
}