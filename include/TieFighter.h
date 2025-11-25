#ifndef TIEFIGHTER_H
#define TIEFIGHTER_H

#pragma once
#include "Cube.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Object.h"
#include "TieWing.h"
#include "Texture.h"
#include <vector>
#include <memory>

class TieFighter : public Object{
public:

    TieFighter(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl);
    TieFighter(glm::vec3 pos);

    void init();
    void draw(Shader &shader, glm::mat4 model);

private:

    std::vector<std::unique_ptr<Object>> parts;

};


#endif // TIEFIGHTER_H
