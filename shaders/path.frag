#version 330 core


uniform vec2 u_x0;           // initial position in world space
uniform vec2 u_v0;

bool comp(float a, float b){
    if(u_v0.x > 0){
        return a > b;
    } else {
        return a < b;
    }
}
void main() {
    float len = length(vec2(u_x0.x, 600-u_x0.y)-gl_FragCoord.xy);
    if(comp(gl_FragCoord.x, u_x0.x) || len > 300){
        gl_FragColor = vec4(0,0,0,0);
    } else {
        gl_FragColor = vec4(1.0);
    }
}
