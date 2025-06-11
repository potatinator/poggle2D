#version 330 core

uniform vec2 u_resolution;   // screen size
uniform vec2 u_x0;           // initial position in world space
uniform vec2 u_v0;           // initial velocity in world space
uniform float u_g;            // gravity (e.g., vec2(0.0, -9.8))

float positionAtTime(float t, vec2 x0, vec2 v0, float g) {
    return 600 - -(x0.y + (v0.y/v0.x)*(t-x0.x) - (g/(2*pow(v0.x, 2)))*pow(t-x0.x, 2));
}


void main() {
    vec3 screenPos = vec3(gl_FragCoord.xy, 1.0);
    int thickness = 5;
    float minDist = 1000;

    for (float dx = -thickness/2; dx <= thickness/2; dx += 0.5) {
        float x = screenPos.x + dx;
        float y = positionAtTime(x, u_x0, u_v0, u_g);
        float dist = length(vec2(x, y) - screenPos.xy);
        minDist = min(minDist, dist);
    }

    float alpha = smoothstep(thickness, thickness - 1.0, minDist);
    vec3 color = mix(vec3(0.0), vec3(1.0), alpha);
    
    gl_FragColor = vec4(color, 1.0);
}
