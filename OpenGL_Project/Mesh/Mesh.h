#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Shader.h"
#include <glad/glad.h>
struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture
{
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh
{
public:
    Mesh(float vertices[])
    {
        this->vertices.resize(36);
        memcpy(&(this->vertices[0]), vertices, 36 * 8 * sizeof(float));
        SetUpMesh();
    }

    Mesh(std::vector<Vertex> vertexs,
        std::vector<unsigned int> indices,
        std::vector<Texture> textures)
    {
        this->vertices = vertexs;
        this->indices = indices;
        this->textures = textures;
        SetUpMesh();
    }

    ~Mesh()
    {

    };

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    void Draw(Shader* shader)
    {
        for (unsigned int i = 0; i < textures.size(); i++)
        {
            if (textures[i].type == "texture_diffuse")
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textures[i].id);
                shader->SetUniform1i("material.diffuse", 0);
            }
            else if (textures[i].type == "texture_speclar")
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textures[i].id);
                shader->SetUniform1i("material.specular", 1);
            }
        }
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
    };

private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    void SetUpMesh()
    {
        //VAO
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        //VBO
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

        //EBO
        /*glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices.data()), indices.data(), GL_STATIC_DRAW);*/

        //启用0号位
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(GL_FLOAT)));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(GL_FLOAT)));
    };
};
