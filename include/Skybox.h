#ifndef SKYBOX_H
#define SKYBOX_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Shader.h>

class Skybox {
public:
    Skybox();
    ~Skybox();

    void draw(const glm::mat4& view, const glm::mat4& projection);

private:
    unsigned int skyboxVAO, skyboxVBO;
    Shader* shader;
};

#endif
