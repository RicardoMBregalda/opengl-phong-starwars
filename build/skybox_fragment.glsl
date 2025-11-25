#version 330 core
out vec4 FragColor;
in vec3 TexCoords;

float rand(vec2 co) {
    return fract(sin(dot(co.xy, vec2(12.9898,7.233))) * 43758.5453);
}

void main()
{
    float brightness = rand(TexCoords.xy * 500.0);
    if (brightness > 0.995) {
        FragColor = vec4(1.0); // estrela branca
    } else {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0); // espaço preto
    }
}

