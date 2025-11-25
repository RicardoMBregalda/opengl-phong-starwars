#ifndef HEXPRISM_H
#define HEXPRISM_H

#include <vector>
#include <cmath>

class HexPrism {
public:
    unsigned int VAO, VBO, EBO;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    //HexPrism() {}

    HexPrism(float radius = 0.5f, float height = 1.0f) {
        generateHexPrism(radius, height);
        setupBuffers();
    }

    void draw(Shader &shader, glm::mat4 model) {
        model = glm::translate(model, position);
        model = glm::scale(model, scale);

        shader.setMat4("model", model);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }

private:
    void generateHexPrism(float radius, float height) {
        vertices.clear();
        indices.clear();

        float halfHeight = height / 2.0f;
        int segments = 6;
        float step = 2.0f * M_PI / segments;

        // --- TOPO ---
        // centro do topo
        vertices.insert(vertices.end(), {0.0f, halfHeight, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f});
        int topCenterIndex = 0;

        for (int i = 0; i <= segments; i++) {
            float theta = i * step;
            float x = radius * cos(theta);
            float z = radius * sin(theta);
            float u = (cos(theta) + 1.0f) * 0.5f;
            float v = (sin(theta) + 1.0f) * 0.5f;
            vertices.insert(vertices.end(), {x, halfHeight, z, u, v, 0.0f, 1.0f, 0.0f});
        }

        // --- BASE ---
        int baseCenterIndex = (int)vertices.size() / 8;
        vertices.insert(vertices.end(), {0.0f, -halfHeight, 0.0f, 0.5f, 0.5f, 0.0f, -1.0f, 0.0f});

        for (int i = 0; i <= segments; i++) {
            float theta = i * step;
            float x = radius * cos(theta);
            float z = radius * sin(theta);
            float u = (cos(theta) + 1.0f) * 0.5f;
            float v = (sin(theta) + 1.0f) * 0.5f;
            vertices.insert(vertices.end(), {x, -halfHeight, z, u, v, 0.0f, -1.0f, 0.0f});
        }

        // --- LATERAL ---
        int sideStartIndex = (int)vertices.size() / 8;
        for (int i = 0; i <= segments; i++) {
            float theta = i * step;
            float x = radius * cos(theta);
            float z = radius * sin(theta);
            float u = 1.0f - (float)i / segments;
            float nx = cos(theta);
            float nz = sin(theta);

            // topo
            vertices.insert(vertices.end(), {x, halfHeight, z, u, 1.0f, nx, 0.0f, nz});
            // base
            vertices.insert(vertices.end(), {x, -halfHeight, z, u, 0.0f, nx, 0.0f, nz});
        }

        // --- ÍNDICES ---
        // topo (triângulos em fan)
        for (int i = 1; i <= segments; i++) {
            indices.push_back(topCenterIndex);
            indices.push_back(i);
            indices.push_back(i + 1);
        }

        // base (triângulos em fan)
        for (int i = 1; i <= segments; i++) {
            indices.push_back(baseCenterIndex);
            indices.push_back(baseCenterIndex + i + 1);
            indices.push_back(baseCenterIndex + i);
        }

        // laterais (triangle strip convertido para triângulos)
        for (int i = 0; i < segments; i++) {
            int top1 = sideStartIndex + i * 2;
            int bot1 = top1 + 1;
            int top2 = top1 + 2;
            int bot2 = bot1 + 2;

            indices.push_back(top1);
            indices.push_back(bot1);
            indices.push_back(top2);

            indices.push_back(top2);
            indices.push_back(bot1);
            indices.push_back(bot2);
        }
    }

    void setupBuffers() {
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
};

#endif
