#pragma once

#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Material
{
public:
    Shader* shader;
    unsigned int diffuse;
    glm::vec3 specular;
    glm::vec3 ambient;
    float shininess;
    Material(Shader* shader, unsigned int diffuse, glm::vec3 specular, glm::vec3 ambient, float shininess);
};

