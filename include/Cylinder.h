#ifndef CYLINDER_H
#define CYLINDER_H

#include <glm/glm.hpp>
#include "Shader.h"
#include "Object.h"
#include <vector>

class Cylinder : public Object {
public:

    float angle;

    Cylinder() {}
    Cylinder(glm::vec3 pos, float radius = 0.5f, float height = 1.0f, int segments = 36, float ang=0.0f);
    Cylinder(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float radius = 0.5f, float height = 1.0f, int segments = 36, float ang=0.0f);
    void draw(Shader &shader, glm::mat4 model);

private:

    unsigned int VAO, VBO, EBO;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    void init(float radius, float height, int segments);
};

#endif
