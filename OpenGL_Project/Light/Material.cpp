#include "Material.h"

Material::Material(Shader* shader, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 ambient, float shininess)
{
    this->diffuse = diffuse;
    this->ambient = ambient;
    this->specular = specular;
    this->shininess = shininess;
    this->shader = shader;

}