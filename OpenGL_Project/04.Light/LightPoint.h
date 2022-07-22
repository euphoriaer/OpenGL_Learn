#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

class LightPoint
{
public:
    LightPoint(glm::vec3 position, glm::vec3 angles, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f))
    {
        this->position = position;
        this->color = color;
        this->angles = angles;
    };
    ~LightPoint()
    {
    };

    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 angles;
    glm::vec3 direction = glm::vec3(0, 0, 1.0f);

    float constant = 1.0f;
    float linear = 0.1f;
    float quadratic = 0.032f;
};
