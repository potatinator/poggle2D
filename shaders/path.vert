#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 TexCoords;

uniform int layer;
uniform mat4 transform;
uniform mat4 view;

uniform vec2 u_resolution;   // screen size
uniform vec2 u_x0;           // initial position in world space
uniform vec2 u_v0;           // initial velocity in world space
uniform float u_g;            // gravity (e.g., vec2(0.0, -9.8))

out vec2 coords;

float positionAtTime(float t, vec2 x0, vec2 v0, float g) {
    return -(x0.y + (v0.y/v0.x)*(t-x0.x) - (g/(2*pow(v0.x, 2)))*pow(t-x0.x, 2));
}

void main()
{
    vec3 pos = (transform*vec4(aPos, layer, 1.0)).xyz;
    vec3 screenPos = vec3(pos.xy, 1.0);
    int thickness = 5;
    float minDist = 1000;

    pos.y = positionAtTime(pos.x, u_x0, u_v0, u_g);

    coords = TexCoords;
    gl_Position = view * vec4(pos, 1.0); 
}  