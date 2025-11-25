#ifndef HEXAGONALPRISM_H
#define HEXAGONALPRISM_H

#pragma once
#include "Hexagon.h"

class HexagonalPrism : public Hexagon {
public:
    HexagonalPrism(glm::vec3 pos, float radiusTop, float radiusBottom, float height, float angle = 0.0f);
    HexagonalPrism(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl,
                   float radiusTop, float radiusBottom, float height, float angle = 0.0f);

protected:
    void init(float radiusTop, float radiusBottom, float height);
};


#endif // HEXAGONALPRISM_H
