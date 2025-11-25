#ifndef XWINGCLOSED_H
#define XWINGCLOSED_H

#pragma once
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Object.h>
#pragma once
#include "Cube.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Object.h"
#include "TieWing.h"
#include "Texture.h"
#include <vector>
#include <memory>

class XWingClosed : public Object{
public:

    float angle;
    XWingClosed(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle);
    XWingClosed(glm::vec3 pos, float angle);

    void init();
    void draw(Shader &shader, glm::mat4 model);

private:

    std::vector<std::unique_ptr<Object>> parts;

};


#endif // XWINGCLOSED_H
