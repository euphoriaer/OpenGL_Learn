#pragma once
#include <vector>
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "Main.h"

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
    std::vector<Texture> textures_loaded;
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
        std::vector<Texture> textures;

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

        //处理索引
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            
            for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
            {
                tempIndices.push_back(mesh->mFaces[i].mIndices[j]);
            }

        }
        
        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            std::vector<Texture> diffuseMaps = loadMaterialTextures(material,
                aiTextureType_DIFFUSE, "texture_diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            std::vector<Texture> specularMaps = loadMaterialTextures(material,
                aiTextureType_SPECULAR, "texture_specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        }

        return Mesh(tempVertices,tempIndices,{});
    }
    
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
    {

        std::vector<Texture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            bool skip = false;

            for (unsigned int j = 0; j < textures_loaded.size(); j++)
            {
                if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(textures_loaded[j]);
                    skip = true;
                    break;
                }
            }
            if (!skip)
            {   // 如果纹理还没有被加载，则加载它
                Texture texture;
                texture.id = LoadImageToGPU(str.C_Str(), GL_RGBA, GL_RGBA, 1);
                texture.type = typeName;
                texture.path = str.C_Str();
                textures.push_back(texture);
                textures_loaded.push_back(texture); // 添加到已加载的纹理中
            }
        }
        return textures;


    }
};
