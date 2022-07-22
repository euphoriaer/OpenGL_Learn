#pragma once
#include <vector>
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

class Model
{
public:
    Model(std::string path)
    {
        loadModel(path);
    };
    ~Model()
    {
    };
    void Draw(Shader* shader)
    {
        for (unsigned int i = 0; i < meshes.size(); i++)
        {
            meshes[i].Draw(shader);
        }
    }
    std::string directory;
    std::vector<Mesh> meshes;
private:
    void loadModel(std::string path)
    {
        Assimp::Importer impoter;
        const aiScene* scene = impoter.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE||!scene->mRootNode)
        {
            std::cout << "Assimp error" << std::endl;
            return;
        }
        directory = path.substr(0, path.find_last_of('\\'));

        std::cout << "loadModel directory:  " << directory << std::endl;
        processNode(scene->mRootNode, scene);
    };
    void processNode(aiNode* node, const aiScene* scene)
    {
        std::cout << node->mName.data << std::endl;

        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            auto curMesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(curMesh,scene));
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }
    }
    
    Mesh  processMesh(aiMesh* mesh, const aiScene* scene)
    {
        std::vector<Vertex> tempVertices;
        std::vector<unsigned int> tempIndices;
        std::vector<Texture> tempTextures;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex tempVertex;
            tempVertex.Position.x = mesh->mVertices[i].x;
            tempVertex.Position.y = mesh->mVertices[i].y;
            tempVertex.Position.z = mesh->mVertices[i].z;
            

            tempVertex.Normal.x = mesh->mNormals[i].x;
            tempVertex.Normal.y = mesh->mNormals[i].y;
            tempVertex.Normal.z = mesh->mNormals[i].z;

            if (mesh->mTextureCoords[0])
            {
                tempVertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
                tempVertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
            }
            else
            {
                tempVertex.TexCoords = glm::vec2(0, 0);
            }
            tempVertices.push_back(tempVertex);
        }


        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            
            for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
            {
                tempIndices.push_back(mesh->mFaces[i].mIndices[j]);
            }

        }

        return Mesh(tempVertices,tempIndices,{});
    }
};
