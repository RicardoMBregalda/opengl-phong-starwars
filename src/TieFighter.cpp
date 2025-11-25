#include "TieFighter.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "TieWing.h"
#include "Object.h"
#include "Texture.h"

TieFighter::TieFighter(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl)
    : Object(pos, rot, scl)
{
    // Cada parte da nave será um "sub-modelo"

    init();
}

TieFighter::TieFighter(glm::vec3 pos)
    : Object(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f))
{
    init();
}

void TieFighter::init() {


    // Esfera central do cockpit
    parts.push_back(std::make_unique<Sphere>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.5f)));
    // Hastes de ligação
    parts.push_back(std::make_unique<Cube>(glm::vec3(-0.35f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.4f, 0.1f, 0.2f)));
    parts.push_back(std::make_unique<Cube>(glm::vec3(0.35f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.38f, 0.1f, 0.2f)));
    // Asas
    parts.push_back(std::make_unique<TieWing>(glm::vec3(-0.6f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.5f, 1.5f, 1.0f)));
    parts.push_back(std::make_unique<TieWing>(glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.5f, 1.5f, 1.0f)));

}

void TieFighter::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::scale(model, scale);


    for (auto &part : parts) {
        part->draw(shader, model);
    }
}

