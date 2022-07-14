#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

class LightDirectional
{
public :
    LightDirectional();
    ~LightDirectional();

    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 angles;
    glm::vec3 direction = glm::vec3(0, 0, 1.0f);

    void UpdateDirection()
    {
        direction= glm::vec3(0, 0, 1.0f);
        direction = glm::rotateZ(direction, angles.z);
        direction = glm::rotateX(direction, angles.x);
        direction = glm::rotateY(direction, angles.y);
    }
};

