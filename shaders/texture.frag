#version 330 core

out vec4 FragColor;

in vec2 coords;

uniform sampler2D tex;
uniform bool debug;
uniform float exposure = 1.0;

void main()
{
    if(debug){
        FragColor = vec4(1.0, 1.0, 0.0, 1.0);
    } else {
        FragColor = texture(tex, coords);
    }
    FragColor *= vec4(vec3(exposure), 1.0);

}  