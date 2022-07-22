#include "Material.h"

Material::Material(Shader* shader,unsigned int diffuse, unsigned int specular,unsigned int  emissive, glm::vec3 ambient, float shininess)
{
    this->emissive = emissive;
    this->diffuse = diffuse;
    this->ambient = ambient;
    this->specular = specular;
    this->shininess = shininess;
    this->shader = shader;

}
