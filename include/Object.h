#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include "Shader.h"


class Object
{
    public:

        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        Object() {}
        Object(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl)
        : position(pos), rotation(rot), scale(scl) {}
        virtual ~Object() {}
        virtual void draw(Shader &shader, glm::mat4 model) = 0;

    protected:

    private:
};

#endif // OBJECT_H
