#version 330 core

out vec4 FragColor;
uniform vec3 uDefaultColor;

void main()
{
    FragColor = vec4(uDefaultColor, 1.0); // Orange color
}
