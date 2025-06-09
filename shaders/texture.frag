#version 330 core

out vec4 FragColor;

in vec2 coords;

uniform sampler2D tex;
uniform bool debug;
uniform bool hit;

void main()
{
    if(debug){
        FragColor = vec4(1.0, 1.0, 0.0, 1.0);
    } else {
        FragColor = texture(tex, coords);
    }
    if(hit){
        FragColor *= vec4(vec3(50), 1.0);
    }
}  