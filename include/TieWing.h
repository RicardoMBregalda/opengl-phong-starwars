#ifndef TIEWING_H
#define TIEWING_H

#pragma once
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Object.h>

class TieWing : public Object {
public:

    TieWing(glm::vec3 pos = glm::vec3(0.0f),
         glm::vec3 rot = glm::vec3(0.0f),
         glm::vec3 scl = glm::vec3(1.0f));

    void draw(Shader &shader, glm::mat4 model);

private:
    unsigned int VAO, VBO, EBO;
    void init();
};


#endif // TIEWING_H
