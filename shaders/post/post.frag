#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform sampler2D bloomTexture;
uniform float time;

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

vec3 whitenHighlights(vec3 color, float threshold)
{
    float lum = dot(color, vec3(0.2126, 0.7152, 0.0722));
    float t = smoothstep(threshold, threshold * 4.0, lum); // tweak range
    return mix(color, vec3(lum), t);
}

vec3 ACESFittedTonemap(vec3 color)
{
    color = pow(color, vec3(1.0 / 2.2));

    float exposureBias = 0.8;
    color *= exposureBias;

    color = (color*(2.51*color+0.03))/(color*(2.43*color+0.59)+0.14);//bright parts dont get low sat


    // Clamp to displayable range
    color = clamp(color, 0.0, 1.0);


    return color;
}
void main()
{

    //normal
    FragColor = texture(screenTexture, TexCoords);
    //-----------------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------------
    //kernel
    // vec2 pix = vec2(1.0/800.0, 1.0/600.0);//800 and 600 are image dims

    // int size = 3;//side length of kernel
    // float kernel[9] = float[](
        // 0.0625, 0.125, 0.0625,
        // 0.125 , 0.25 , 0.125,
        // 0.0625, 0.125, 0.0625
    // );
    // vec3 sampleTex[kernel.length()];
    // vec2 mid = vec2((size-1)/2);
    // for(int i = 0; i < size; i++)
    // {
        // for(int j = 0; j < size; j++)
        // {
            // sampleTex[(size*i)+j] = vec3(texture(screenTexture, TexCoords.st + (mid-vec2(j,i))*pix));
        // }
    // }
    // vec3 col = vec3(0.0);
    // for(int i = 0; i < kernel.length(); i++)
        // col += sampleTex[i] * kernel[i];
    // FragColor = vec4(col, 1.0);
    //-----------------------------------------------------------------------------------------
    //rotate
    // vec3 col = texture(screenTexture, vec2(1.0-TexCoords.y, TexCoords.x)).rgb;
    // FragColor = vec4(col, 1.0);
    //-----------------------------------------------------------------------------------------
    //tone mapping
    vec3 color = FragColor.rgb;

    float luminance = dot(color, vec3(0.3, 0.59, 0.11));
    float desatFactor = clamp((1.0 - luminance) / 0.5, 0.0, 1.0);
    color = mix(vec3(luminance), color, desatFactor);

    color = ACESFittedTonemap(color);

    // FragColor = vec4(color, 1.0);
    

    //-----------------------------------------------------------------------------------------
    //greyscale
    // col = FragColor;
    // float average = 0.2126 * col.r + 0.7152 * col.g + 0.0722 * col.b;
    // FragColor = vec4(average, average, average, 1.0);
    //-----------------------------------------------------------------------------------------
    //invert
    // col = FragColor;
    // FragColor = vec4(vec3(1.0)-col, 1.0);
    //-----------------------------------------------------------------------------------------
    //noise chanels
    // vec3 col = FragColor;
    // vec2 coord = round(TexCoords*10)/10;
    // FragColor = vec4(clamp((vec3(rand(coord*time), rand(vec2(rand(coord*time), rand(coord.yx*time))), rand(coord.yx*time))-0.5) * 10, 0, 1)*col, 1.0);
    //-----------------------------------------------------------------------------------------
    
} 