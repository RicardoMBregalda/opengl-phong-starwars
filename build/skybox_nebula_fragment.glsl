#version 330 core
out vec4 FragColor;
in vec3 TexCoords;

uniform float time;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

// Perlin/Simplex aqui seria melhor, mas vamos fingir algo bem simples
float noise(vec2 p) {
    vec2 i = floor(p);
    vec2 f = fract(p);
    float a = rand(i);
    float b = rand(i + vec2(1.0, 0.0));
    float c = rand(i + vec2(0.0, 1.0));
    float d = rand(i + vec2(1.0, 1.0));
    vec2 u = f*f*(3.0-2.0*f);
    return mix(a, b, u.x) +
           (c - a)* u.y * (1.0 - u.x) +
           (d - b) * u.x * u.y;
}

void main()
{
    vec2 uv = TexCoords.xy * 5.0; // escala
    float n = noise(uv + time*0.05);

    vec3 color = mix(vec3(0.1, 0.0, 0.2), vec3(0.8, 0.3, 1.0), n); // roxo/rosa nebulosa
    FragColor = vec4(color, n*0.6); // com alpha
}

