#version 330 core

uniform vec2 u_resolution;   // screen size
uniform vec2 u_x0;           // initial position in world space
uniform vec2 u_v0;           // initial velocity in world space
uniform float u_g;            // gravity (e.g., vec2(0.0, -9.8))

float positionAtTime(float t, vec2 x0, vec2 v0, float g) {
    return 600 - -(x0.y + (v0.y/v0.x)*(t-x0.x) - (g/(2*pow(v0.x, 2)))*pow(t-x0.x, 2));
}

bool comp(float a, float b){
    if(u_v0.x > 0){
        return a > b;
    } else {
        return a < b;
    }
}

void main() {
    vec3 screenPos = vec3(gl_FragCoord.xy, 1.0);
    int thickness = 2;
    int search = 10;
    float minDist = 1000;

    float diff = mix(0.05, 1.0, abs(screenPos.x - u_x0.x)/800.0);
    for (float dx = -search; dx <= search; dx += diff) {
        float x = screenPos.x + dx;
        float y = positionAtTime(x, u_x0, u_v0, u_g);
        float dist = length(vec2(x, y) - screenPos.xy);
        minDist = min(minDist, dist);
    }

    // float alpha = smoothstep(thickness, thickness - 1.0, minDist);
    // vec4 color = mix(vec4(0.0), vec4(1.0), alpha);
    vec4 color = mix(vec4(0.0), vec4(1), (minDist < thickness) ? 1.0 : 0.0);

    gl_FragColor = color;

    float len = length(vec2(u_x0.x, 600-u_x0.y)-gl_FragCoord.xy);
    if(comp(gl_FragCoord.x, u_x0.x) || len > 300){
        gl_FragColor = vec4(0,0,0,0);
    }
}
