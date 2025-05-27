#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 TexCoords;

uniform int layer;
uniform mat4 transform;
uniform mat4 view;

out vec2 coords;

void main()
{
    coords = TexCoords;
    gl_Position = view*transform*vec4(aPos, layer, 1.0); 
}  