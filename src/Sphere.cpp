#include "Sphere.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>


Sphere::Sphere(glm::vec3 pos, float radius, int sectors, int stacks)
    : Object(pos, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)) {
    init(radius, sectors, stacks);
}

Sphere::Sphere(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float radius, int sectors, int stacks)
    : Object(pos,rot,scl) {
    init(radius, sectors, stacks);
}

void Sphere::init(float radius, int sectors, int stacks) {
    vertices.clear();
    indices.clear();

    float sectorStep = 2.0f * M_PI / sectors;
    float stackStep  = M_PI / stacks;

    for (int i = 0; i <= stacks; ++i) {
        float stackAngle = M_PI / 2.0f - i * stackStep; // de +pi/2 até -pi/2
        float xy = radius * cosf(stackAngle);
        float y  = radius * sinf(stackAngle);

        for (int j = 0; j <= sectors; ++j) {
            float sectorAngle = j * sectorStep;

            float x = xy * cosf(sectorAngle);
            float z = xy * sinf(sectorAngle);

            float u = 1.0f - (float)j / sectors;
            float v = 1.0 - (float)i / stacks;

            float nx = x / radius;
            float ny = y / radius;
            float nz = z / radius;

            vertices.insert(vertices.end(), {x, y, z, u, v, nx, ny, nz});

        }
    }

    // gera índices
    for (int i = 0; i < stacks; ++i) {
        int k1 = i * (sectors + 1);
        int k2 = k1 + sectors + 1;

        for (int j = 0; j < sectors; ++j, ++k1, ++k2) {
            if (i != 0) { // triângulo de cima
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
            if (i != (stacks - 1)) { // triângulo de baixo
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    // OpenGL buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // posição (3 floats) + tex coords (2 floats) + normals (3 floats)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Sphere::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
