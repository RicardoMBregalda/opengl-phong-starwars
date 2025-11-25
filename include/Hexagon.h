// Hexagon.h
#ifndef HEXAGON_H
#define HEXAGON_H

#include <glm/glm.hpp>
#include <vector>
#include "Shader.h"
#include "Object.h"

class Hexagon : public Object {
public:

    float angle;

    Hexagon() {}

    Hexagon(glm::vec3 pos, float radius, float height, float angle );
    Hexagon(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float radius, float height, float angle);

    void draw(Shader &shader, glm::mat4 model);

protected:

    unsigned int VAO, VBO, EBO;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

private:

    void init(float radius, float height);
};

#endif
