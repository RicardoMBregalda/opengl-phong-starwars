#include "TieWing.h"

TieWing::TieWing(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl)
    : Object(pos, rot, scl) {
    init();
}

void TieWing::init() {

    // Normais para cada face:
    // Face frontal (x=0): normal = (-1, 0, 0)
    // Face traseira (x=0.1): normal = (1, 0, 0)
    // Face lateral A-C (superior esquerda): normal calculada
    // Face lateral C-D (topo): normal = (0, 1, 0)
    // Face lateral D-B (superior direita): normal calculada
    // Face lateral B-F (inferior direita): normal calculada
    // Face lateral F-E (fundo): normal = (0, -1, 0)
    // Face lateral E-A (inferior esquerda): normal calculada

    // Normais aproximadas para as laterais do hexágono:
    // A-C: direção de (0,0,-0.6) para (0,0.5,-0.3) -> normal apontando para fora
    // Normal A-C: normalize(0.5, 0.3, 0) aproximadamente (0.857, 0.514, 0) -> simplificando (0.6, 0.8, 0) normalizado
    // Vamos calcular as normais das faces laterais:

    // Face A-C: de A(0,0,-0.6) para C(0,0.5,-0.3) 
    // Borda: (0, 0.5, 0.3), espessura: (0.1, 0, 0)
    // Normal = cross((0,0.5,0.3), (0.1,0,0)) = (0.5*0 - 0.3*0, 0.3*0.1 - 0*0, 0*0 - 0.5*0.1) = (0, 0.03, -0.05)
    // Normalizado: (0, 0.514, -0.857) 

    // Face C-D: de C(0,0.5,-0.3) para D(0,0.5,0.3)
    // Normal = (0, 1, 0)

    // Face D-B: de D(0,0.5,0.3) para B(0,0,0.6)
    // Borda: (0, -0.5, 0.3), espessura: (0.1, 0, 0)
    // Normal = cross((0,-0.5,0.3), (0.1,0,0)) = (0, 0.03, 0.05) normalizado: (0, 0.514, 0.857)

    // Face B-F: de B(0,0,0.6) para F(0,-0.5,0.3)
    // Borda: (0, -0.5, -0.3), espessura: (0.1, 0, 0)
    // Normal = cross((0,-0.5,-0.3), (0.1,0,0)) = (0, -0.03, 0.05) normalizado: (0, -0.514, 0.857)

    // Face F-E: de F(0,-0.5,0.3) para E(0,-0.5,-0.3)
    // Normal = (0, -1, 0)

    // Face E-A: de E(0,-0.5,-0.3) para A(0,0,-0.6)
    // Borda: (0, 0.5, -0.3), espessura: (0.1, 0, 0)
    // Normal = cross((0,0.5,-0.3), (0.1,0,0)) = (0, -0.03, -0.05) normalizado: (0, -0.514, -0.857)

    float vertices2[] = {
        // Face frontal (x=0) - normal (-1, 0, 0)
        0.0f, 0.0f, -0.6f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // A 1
        0.0f, 0.5f, -0.3f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, // C 2
        0.0f, 0.0f,  0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, // G 3

        0.0f, 0.5f, -0.3f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // C 2
        0.0f, 0.5f,  0.3f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, // D 4
        0.0f, 0.0f,  0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, // G 3

        0.0f, 0.5f,  0.3f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // D 4
        0.0f, 0.0f,  0.6f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, // B 5
        0.0f, 0.0f,  0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, // G 3

        0.0f, 0.0f,  0.6f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // B 5
        0.0f, -0.5f, 0.3f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, // F 6
        0.0f, 0.0f,  0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, // G 3

        0.0f, -0.5f,  0.3f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // F 6
        0.0f, -0.5f, -0.3f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, // E 7
        0.0f, 0.0f,   0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, // G 3

        0.0f, -0.5f, -0.3f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // E 7
        0.0f, 0.0f, -0.6f,  0.0f, 1.0f, -1.0f, 0.0f, 0.0f, // A 1
        0.0f, 0.0f,   0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, // G 3

        // Face traseira (x=0.1) - normal (1, 0, 0)
        0.1f, 0.0f, -0.6f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // A1 8
        0.1f, 0.5f, -0.3f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // C1 9
        0.1f, 0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // G1 10

        0.1f, 0.5f, -0.3f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // C1 9
        0.1f, 0.5f,  0.3f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // D1 11
        0.1f, 0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // G1 10

        0.1f, 0.5f,  0.3f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // D1 11
        0.1f, 0.0f,  0.6f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // B1 12
        0.1f, 0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // G1 10

        0.1f, 0.0f,  0.6f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // B1 12
        0.1f, -0.5f, 0.3f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // F1 13
        0.1f, 0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // G1 10

        0.1f, -0.5f,  0.3f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // F1 13
        0.1f, -0.5f, -0.3f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // E1 14
        0.1f, 0.0f,   0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // G1 10

        0.1f, -0.5f, -0.3f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // E1 14
        0.1f, 0.0f,  -0.6f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // A1 8
        0.1f, 0.0f,   0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // G1 10

        // Face lateral A-C - normal (0, 0.514, -0.857)
        0.0f, 0.0f, -0.6f, 1.0f, 1.0f, 0.0f, 0.514f, -0.857f, // A 1
        0.1f, 0.0f, -0.6f, 1.0f, 0.0f, 0.0f, 0.514f, -0.857f, // A1 8
        0.1f, 0.5f, -0.3f, 0.0f, 0.0f, 0.0f, 0.514f, -0.857f, // C1 9
        0.1f, 0.5f, -0.3f, 1.0f, 1.0f, 0.0f, 0.514f, -0.857f, // C1 9
        0.0f, 0.5f, -0.3f, 1.0f, 0.0f, 0.0f, 0.514f, -0.857f, // C 2
        0.0f, 0.0f, -0.6f, 0.0f, 0.0f, 0.0f, 0.514f, -0.857f, // A 1

        // Face lateral C-D (topo) - normal (0, 1, 0)
        0.0f, 0.5f, -0.3f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // C 2
        0.1f, 0.5f, -0.3f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // C1 9
        0.1f, 0.5f,  0.3f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // D1 11
        0.1f, 0.5f,  0.3f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // D1 11
        0.0f, 0.5f,  0.3f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // D 4
        0.0f, 0.5f, -0.3f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // C 2

        // Face lateral D-B - normal (0, 0.514, 0.857)
        0.0f, 0.5f,  0.3f, 1.0f, 1.0f, 0.0f, 0.514f, 0.857f, // D 4
        0.1f, 0.5f,  0.3f, 1.0f, 0.0f, 0.0f, 0.514f, 0.857f, // D1 11
        0.1f, 0.0f,  0.6f, 0.0f, 0.0f, 0.0f, 0.514f, 0.857f, // B1 12
        0.1f, 0.0f,  0.6f, 1.0f, 1.0f, 0.0f, 0.514f, 0.857f, // B1 12
        0.0f, 0.0f,  0.6f, 1.0f, 0.0f, 0.0f, 0.514f, 0.857f, // B 5
        0.0f, 0.5f,  0.3f, 0.0f, 0.0f, 0.0f, 0.514f, 0.857f, // D 4

        // Face lateral B-F - normal (0, -0.514, 0.857)
        0.0f, 0.0f,  0.6f, 1.0f, 1.0f, 0.0f, -0.514f, 0.857f, // B 5
        0.1f, 0.0f,  0.6f, 1.0f, 0.0f, 0.0f, -0.514f, 0.857f, // B1 12
        0.1f, -0.5f, 0.3f, 0.0f, 0.0f, 0.0f, -0.514f, 0.857f, // F1 13
        0.1f, -0.5f, 0.3f, 1.0f, 1.0f, 0.0f, -0.514f, 0.857f, // F1 13
        0.0f, -0.5f, 0.3f, 1.0f, 0.0f, 0.0f, -0.514f, 0.857f, // F 6
        0.0f, 0.0f,  0.6f, 0.0f, 0.0f, 0.0f, -0.514f, 0.857f, // B 5

        // Face lateral F-E (fundo) - normal (0, -1, 0)
        0.0f, -0.5f, 0.3f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f, // F 6
        0.1f, -0.5f, 0.3f,  1.0f, 1.0f, 0.0f, -1.0f, 0.0f, // F1 13
        0.1f, -0.5f, -0.3f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, // E1 14
        0.1f, -0.5f, -0.3f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, // E1 14
        0.0f, -0.5f, -0.3f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, // E 7
        0.0f, -0.5f, 0.3f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f, // F 6

        // Face lateral E-A - normal (0, -0.514, -0.857)
        0.0f, -0.5f, -0.3f, 1.0f, 1.0f, 0.0f, -0.514f, -0.857f, // E 7
        0.1f, -0.5f, -0.3f, 1.0f, 0.0f, 0.0f, -0.514f, -0.857f, // E1 14
        0.1f, 0.0f, -0.6f,  0.0f, 0.0f, 0.0f, -0.514f, -0.857f, // A1 8
        0.1f, 0.0f, -0.6f,  1.0f, 1.0f, 0.0f, -0.514f, -0.857f, // A1 8
        0.0f, 0.0f, -0.6f,  1.0f, 0.0f, 0.0f, -0.514f, -0.857f, // A 1
        0.0f, -0.5f, -0.3f, 0.0f, 0.0f, 0.0f, -0.514f, -0.857f  // E 7
    };


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    // position (3 floats) + tex coords (2 floats) + normals (3 floats)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // tex coords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // normals
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void TieWing::draw(Shader &shader, glm::mat4 model) {

    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 72);
    glBindVertexArray(0);
}
