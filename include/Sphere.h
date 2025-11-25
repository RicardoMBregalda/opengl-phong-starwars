#ifndef SPHERE_H
#define SPHERE_H

#include <glm/glm.hpp>
#include "Shader.h"
#include "Object.h"
#include <vector>

class Sphere : public Object {
public:

    Sphere() {}

    Sphere(glm::vec3 pos, float radius = 0.5f, int sectors = 36, int stacks = 18);
    Sphere(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float radius = 0.5f, int sectors = 36, int stacks = 18);
    void draw(Shader &shader, glm::mat4 model);

private:

    unsigned int VAO, VBO, EBO;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    void init(float radius, int sectors, int stacks);
};

#endif
