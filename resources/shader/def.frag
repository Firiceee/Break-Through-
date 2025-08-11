#version 330 core

in vec2 texturePos;

out vec4 ourColor;

uniform sampler2D tex;
uniform vec3 spriteColor;


void main()
{
    ourColor = vec4(spriteColor, 1) * texture(tex, texturePos);
}