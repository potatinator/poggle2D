#version 330 core

out vec4 FragColor;

in vec2 coords;

uniform sampler2D tex;
uniform bool debug;

void main()
{
    if(debug){
        FragColor = vec4(1.0, 1.0, 0.0, 1.0);
    } else {
        FragColor = texture(tex, coords);
    }
}  