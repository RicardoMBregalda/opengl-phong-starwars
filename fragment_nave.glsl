#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    vec4 tex = texture(texture1, TexCoord);

    // opcional: descarta pixels completamente transparentes
    // (ajuda a não escrever profundidade)
    if (tex.a < 0.05)
        discard;

    FragColor = tex;
}
