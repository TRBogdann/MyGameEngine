#version 450 core

layout (location = 0) uniform vec4 color;

out vec4 FragColor;

void main()
{
    FragColor = color;
}