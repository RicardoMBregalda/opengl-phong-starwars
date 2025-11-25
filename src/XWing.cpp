#include "XWing.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "TieWing.h"
#include "Object.h"
#include "Hexagon.h"
#include "HexagonalPrism.h"
#include "Texture.h"
#include "Plate.h"

XWing::XWing(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle)
    : Object(pos, rot, scl), angle(angle)
{
    // Cada parte da nave será um "sub-modelo"

    init();
}

XWing::XWing(glm::vec3 pos, float angle)
    : Object(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)), angle(angle)
{
    init();
}

void XWing::init() {

    // Corpo nave
    parts.push_back(std::make_unique<Hexagon>(
        glm::vec3(0.28f, -0.15f, 0.0f),     // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(1.0f, 1.0f, 0.8f),      // escala
        0.2f, // raio
        1.1f, // altura
        90.0f
    ));

    //Cockpit
    parts.push_back(std::make_unique<HexagonalPrism>(
        glm::vec3(0.28f, -0.2f, -1.0f),  // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(1.0f, 1.0f, 1.0f),      // escala
        0.06f, 0.15f,                   // raioTopo, raioBase
        1.8f,                           // altura
        268.0f                          // ângulo
    ));

    // Traseira Cockpit
    parts.push_back(std::make_unique<HexagonalPrism>(
        glm::vec3(0.28f, -0.15f, 0.4f),  // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(1.0f, 1.0f, 1.0f),      // escala
        0.2f, 0.15f,                   // raioTopo, raioBase
        0.2f,                           // altura
        270.0f                          // ângulo
    ));

    // Carlinga
    parts.push_back(std::make_unique<HexagonalPrism>(
        glm::vec3(0.28f, -0.1f, -0.5f),  // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(0.8f, 0.8, 1.0f),      // escala
        0.10f, 0.15f,                   // raioTopo, raioBase
        0.35f,                           // altura
        255.0f                          // ângulo
    ));

    // Bico nave
    parts.push_back(std::make_unique<HexagonalPrism>(
        glm::vec3(0.28f, -0.25f, -2.0f),  // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(1.0f, 1.0f, 1.0f),      // escala
        0.08f, 0.02f,                   // raioTopo, raioBase
        0.3f,                           // altura
        80.0f                          // ângulo
    ));

    //Cylinder (Motor) Superior esquerdo
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, 0.0f, 0.0f),     // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(1.0f, 1.0f, 0.8f),      // escala
        0.1f,                             // raio
        1.0f,                             // altura
        36,                               // segmentos
        90.0f                             // ângulo
    ));
    // parte traseira motor superior esquerdo
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, 0.01f, 0.5f),     // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(1.0f, 1.0f, 0.8f),      // escala
        0.07f,                             // raio
        0.5f,                             // altura
        36,                               // segmentos
        90.0f                             // ângulo
    ));

    //Cylinder (Motor) Inferior esquerdo
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, -0.3f, 0.0f),     // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(1.0f, 1.0f, 0.8f),      // escala
        0.1f,                             // raio
        1.0f,                             // altura
        36,                               // segmentos
        90.0f                             // ângulo
    ));
     // parte traseira motor inferior esquerdo
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, -0.33f, 0.4f),     // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(1.0f, 1.0f, 0.8f),      // escala
        0.06f,                             // raio
        0.5f,                             // altura
        36,                               // segmentos
        90.0f                             // ângulo
    ));

    //Cylinder (Motor) Inferior direito
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.58f, -0.3f, 0.0f),     // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(1.0f, 1.0f, 0.8f),      // escala
        0.1f,                             // raio
        1.0f,                             // altura
        36,                               // segmentos
        90.0f                             // ângulo
    ));

    // Parte traseira motor inferior direito
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.58f, -0.33f, 0.4f),     // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(1.0f, 1.0f, 0.8f),      // escala
        0.06f,                             // raio
        0.5f,                             // altura
        36,                               // segmentos
        90.0f                             // ângulo
    ));

    //Cylinder (Motor) Superior direito
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.58f, 0.0f, 0.0f),     // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(1.0f, 1.0f, 0.8f),      // escala
        0.1f,                             // raio
        1.0f,                             // altura
        36,                               // segmentos
        90.0f                             // ângulo
    ));

    // Parte traseira motor superior direito
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.58f, 0.01f, 0.5f),     // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(1.0f, 1.0f, 0.8f),      // escala
        0.07f,                             // raio
        0.5f,                             // altura
        36,                               // segmentos
        90.0f                             // ângulo
    ));

    // Asa inferior esquerda
    parts.push_back(std::make_unique<Plate>(
        glm::vec3(-0.4f, -0.3f, 0.0f),   // posição
        glm::vec3(0.0f, 0.0f, 1.0f),    // rotação (eixo)
        glm::vec3(1.2f, 0.5f, 0.5f),   // escala
        10.0f                            // ângulo
    ));

    // Asa superior esquerda
    parts.push_back(std::make_unique<Plate>(
        glm::vec3(-0.4f, 0.0f, 0.0f),   // posição
        glm::vec3(0.0f, 0.0f, 1.0f),    // rotação (eixo)
        glm::vec3(1.2f, 0.5f, 0.5f),   // escala
        -10.0f                            // ângulo
    ));

    // Asa superior direita
    parts.push_back(std::make_unique<Plate>(
        glm::vec3(0.95f, 0.0f, 0.0f),   // posição
        glm::vec3(0.0f, 0.0f, 1.0f),    // rotação (eixo)
        glm::vec3(1.2f, 0.5f, 0.5f),   // escala
        10.0f                            // ângulo
    ));

    // Asa inferior direita
    parts.push_back(std::make_unique<Plate>(
        glm::vec3(0.95f, -0.3f, 0.0f),   // posição
        glm::vec3(0.0f, 0.0f, 1.0f),    // rotação (eixo)
        glm::vec3(1.2f, 0.5f, 0.5f),   // escala
        -10.0f                            // ângulo
    ));

    //Canhão inferior esquerdo
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(-0.9f, -0.44f, 0.0f),     // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(1.0f, 1.0f, 0.8f),      // escala
        0.04f,                             // raio
        1.0f,                             // altura
        36,                               // segmentos
        90.0f                             // ângulo
    ));
    //  Meio canhão inferior esquerdo
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(-0.9f, -0.44f, -0.8f),     // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(1.0f, 1.0f, 0.8f),      // escala
        0.02f,                             // raio
        1.0f,                             // altura
        36,                               // segmentos
        90.0f                             // ângulo
    ));

    // Canhão inferior direito
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(1.5f, -0.44f, 0.0f),     // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(1.0f, 1.0f, 0.8f),      // escala
        0.04f,                             // raio
        1.0f,                             // altura
        36,                               // segmentos
        90.0f                             // ângulo
    ));

    // Meio canhão inferior direito
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(1.5f, -0.44f, -0.8f),     // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(1.0f, 1.0f, 0.8f),      // escala
        0.02f,                             // raio
        1.0f,                             // altura
        36,                               // segmentos
        90.0f                             // ângulo
    ));

    //Canhão superior direito
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(1.5f, 0.144f, 0.0f),     // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(1.0f, 1.0f, 0.8f),      // escala
        0.04f,                             // raio
        1.0f,                             // altura
        36,                               // segmentos
        90.0f                             // ângulo
    ));


    // Meio canhão superior direito
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(1.5f, 0.144f, -0.8f),     // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(1.0f, 1.0f, 0.8f),      // escala
        0.02f,                             // raio
        1.0f,                             // altura
        36,                               // segmentos
        90.0f                             // ângulo
    ));

    // Canhão Superior esquerdo
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(-0.9f, 0.144f, 0.0f),     // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(1.0f, 1.0f, 0.8f),      // escala
        0.04f,                             // raio
        1.0f,                             // altura
        36,                               // segmentos
        90.0f                             // ângulo
    ));

    // Meio canhão superior esquerdo
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(-0.9f, 0.144f, -0.8f),     // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(1.0f, 1.0f, 0.8f),      // escala
        0.02f,                             // raio
        1.0f,                             // altura
        36,                               // segmentos
        90.0f                             // ângulo
    ));

    // Ponta canhão superior esquerdo
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(-0.9f, 0.144f, -1.25f),     // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(1.0f, 1.0f, 0.8f),      // escala
        0.01f,                             // raio
        0.2f,                             // altura
        36,                               // segmentos
        90.0f                             // ângulo
    ));

    // droide mecanico
    parts.push_back(std::make_unique<Sphere>(glm::vec3(0.28f, 0.0f, -0.3f), glm::vec3(0.0f), glm::vec3(0.15f)));


    //Cube (Ponta laser) inferior esquerdo
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-0.9f, -0.44f, -1.2f),   // posição
        glm::vec3(1.0f, 0.0f, 0.0f),    // rotação (eixo)
        glm::vec3(0.1f, 0.05f, 0.02f),   // escala
        70.0f                            // ângulo
    ));

    //Cube (Ponta laser) superior esquerdo
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-0.9f, 0.144f, -1.2f),   // posição
        glm::vec3(1.0f, 0.0f, 0.0f),    // rotação (eixo)
        glm::vec3(0.1f, 0.05f, 0.02f),   // escala
        70.0f                            // ângulo
    ));

    // Ponta laser superior direito
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(1.5f, 0.144f, -1.2f),   // posição
        glm::vec3(1.0f, 0.0f, 0.0f),    // rotação (eixo)
        glm::vec3(0.1f, 0.05f, 0.02f),   // escala
        70.0f                            // ângulo
    ));

    // Ponta laser inferior direito
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(1.5f, -0.44f, -1.2f),   // posição
        glm::vec3(1.0f, 0.0f, 0.0f),    // rotação (eixo)
        glm::vec3(0.1f, 0.05f, 0.02f),   // escala
        70.0f                            // ângulo
    ));


    // Ponta canhão superior direito
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(1.5f, 0.144f, -1.25f),     // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(1.0f, 1.0f, 0.8f),      // escala
        0.01f,                             // raio
        0.2f,                             // altura
        36,                               // segmentos
        90.0f                             // ângulo
    ));

    // Ponta canhão inferior direito
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(1.5f, -0.44f, -1.25f),     // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(1.0f, 1.0f, 0.8f),      // escala
        0.01f,                             // raio
        0.2f,                             // altura
        36,                               // segmentos
        90.0f                             // ângulo
    ));

    // ponta canhao inferior esquerdo
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(-0.9f, -0.44f, -1.25f),     // posição
        glm::vec3(1.0f, 0.0f, 0.0f),      // rotação (eixo)
        glm::vec3(1.0f, 1.0f, 0.8f),      // escala
        0.01f,                             // raio
        0.2f,                             // altura
        36,                               // segmentos
        90.0f                             // ângulo
    ));

}

void XWing::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    model = glm::rotate(model, glm::radians(angle), rotation);


    for (auto &part : parts) {
        part->draw(shader, model);
    }
}

