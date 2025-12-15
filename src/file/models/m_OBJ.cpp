//
// Created by kisly on 27.10.2025.
//

#include "m_OBJ.hpp"
#include "../../config.hpp"
#include "../../util/Coders.hpp"
#include "../../util/console.hpp"
#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream>

namespace core::model
{
    OBJ::OBJ(const std::string& filepath)
    {
        // Создаем импортер Assimp
        Assimp::Importer importer;

        // Флаги для обработки модели
        unsigned int flags = aiProcess_Triangulate |          // Преобразование в треугольники
            aiProcess_FlipUVs |              // Переворот UV координат
            aiProcess_CalcTangentSpace |     // Вычисление тангенов и битангенов
            aiProcess_GenSmoothNormals |     // Генерация сглаженных нормалей
            aiProcess_JoinIdenticalVertices; // Объединение идентичных вершин

        // Загружаем сцену
        const aiScene* scene = importer.ReadFile(filepath, flags);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            throw Coders(48, importer.GetErrorString());
        }

        if (CORE_INFO)
        {
            console::printTime();
            std::cout << "Ok: load model: " << filepath << std::endl;
            console::printTime();
            std::cout << "Count meshes: " << scene->mNumMeshes << std::endl;
        }

        for (unsigned int i = 0; i < scene->mNumMeshes; i++)
        {
            aiMesh* aiMesh = scene->mMeshes[i];
            Mesh mesh = processMesh(aiMesh, scene);
            this->meshes.push_back(mesh);
        }
    }

    model::Mesh OBJ::processMesh(aiMesh* aiMesh, const aiScene* scene)
    {
        model::Mesh mesh = {};

        if (CORE_INFO)
        {
            console::printTime();
            std::cout << "Mesh name: " << aiMesh->mName.C_Str() << std::endl;
            console::printTime();
            std::cout << "Count polygons: " << aiMesh->mNumFaces << std::endl;
        }

        // Обрабатываем вершины
        for (unsigned int i = 0; i < aiMesh->mNumVertices; i++)
        {
            Vertex vertex;

            // Позиции
            vertex.x = aiMesh->mVertices[i].x;
            vertex.y = aiMesh->mVertices[i].y;
            vertex.z = aiMesh->mVertices[i].z;

            // Нормали
            if (aiMesh->HasNormals())
            {
                vertex.nX = aiMesh->mNormals[i].x;
                vertex.nY = aiMesh->mNormals[i].y;
                vertex.nZ = aiMesh->mNormals[i].z;
            }

            // Текстурные координаты
            if (aiMesh->mTextureCoords[0])
            {
                vertex.u = aiMesh->mTextureCoords[0][i].x;
                vertex.v = aiMesh->mTextureCoords[0][i].y;
            }
            else
            {
                vertex.u = 0.0f;
                vertex.v = 0.0f;
            }

            mesh.vertices.push_back(vertex);
        }

        // Обрабатываем индексы (полигоны)
        for (unsigned int i = 0; i < aiMesh->mNumFaces; i++)
        {
            aiFace face = aiMesh->mFaces[i];

            // Добавляем все индексы полигона (должны быть треугольниками из-за флага aiProcess_Triangulate)
            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                mesh.indices.push_back(face.mIndices[j]);
            }
        }

        // Обработка материалов и текстур
        if (aiMesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[aiMesh->mMaterialIndex];

            // Загружаем диффузные текстуры
            std::vector<Texture> Maps = LoadMaterialTextures(
                material, aiTextureType_DIFFUSE, TEXTURE_TYPE::DIFFUSE);
            if (!Maps.empty())
                mesh.textures.insert(mesh.textures.end(), Maps.begin(), Maps.end());

            // Загружаем specular текстуры
            Maps = LoadMaterialTextures(
                material, aiTextureType_SPECULAR, TEXTURE_TYPE::SPECULAR);
            if (!Maps.empty())
                mesh.textures.insert(mesh.textures.end(), Maps.begin(), Maps.end());

            // Загружаем normal maps
            Maps = LoadMaterialTextures(
                material, aiTextureType_NORMALS, TEXTURE_TYPE::NORMALS);
            if (!Maps.empty())
            mesh.textures.insert(mesh.textures.end(), Maps.begin(), Maps.end());

            Maps = LoadMaterialTextures(
                    material, aiTextureType_AMBIENT, TEXTURE_TYPE::AMBIENT);
            if (!Maps.empty())
                mesh.textures.insert(mesh.textures.end(), Maps.begin(), Maps.end());

            Maps = LoadMaterialTextures(
                    material, aiTextureType_EMISSIVE, TEXTURE_TYPE::EMISSIVE);
            if (!Maps.empty())
                mesh.textures.insert(mesh.textures.end(), Maps.begin(), Maps.end());

            Maps = LoadMaterialTextures(
                    material, aiTextureType_DIFFUSE_ROUGHNESS, TEXTURE_TYPE::DIFFUSE_ROUGHNESS);
            if (!Maps.empty())
                mesh.textures.insert(mesh.textures.end(), Maps.begin(), Maps.end());

            Maps = LoadMaterialTextures(
                    material, aiTextureType_LIGHTMAP, TEXTURE_TYPE::LIGHTMAP);
            if (!Maps.empty())
                mesh.textures.insert(mesh.textures.end(), Maps.begin(), Maps.end());

            Maps = LoadMaterialTextures(
                    material, aiTextureType_DISPLACEMENT, TEXTURE_TYPE::DISPLACEMENT);
            if (!Maps.empty())
                mesh.textures.insert(mesh.textures.end(), Maps.begin(), Maps.end());

            Maps = LoadMaterialTextures(
                    material, aiTextureType_SHININESS, TEXTURE_TYPE::SHININESS);
            if (!Maps.empty())
                mesh.textures.insert(mesh.textures.end(), Maps.begin(), Maps.end());

            Maps = LoadMaterialTextures(
                    material, aiTextureType_REFLECTION, TEXTURE_TYPE::REFLECTION);
            if (!Maps.empty())
                mesh.textures.insert(mesh.textures.end(), Maps.begin(), Maps.end());

            Maps = LoadMaterialTextures(
                    material, aiTextureType_METALNESS, TEXTURE_TYPE::METALNESS);
            if (!Maps.empty())
                mesh.textures.insert(mesh.textures.end(), Maps.begin(), Maps.end());

            Maps = LoadMaterialTextures(
                    material, aiTextureType_OPACITY, TEXTURE_TYPE::OPACITY);
            if (!Maps.empty())
                mesh.textures.insert(mesh.textures.end(), Maps.begin(), Maps.end());
        }

        return mesh;
    }

    std::vector<Texture> OBJ::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, TEXTURE_TYPE typeName) {
        std::vector<Texture> textures = {};
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
            aiString str;
            mat->GetTexture(type, i, &str);

            Texture texture = {};
            texture.type = typeName;
            texture.path = str.C_Str();

            textures.push_back(texture);
        }
        return textures;
    }

    OBJ OBJ::load(const std::string& filepath)
    {
        return OBJ(filepath);
    }

    OBJ* OBJ::ptrLoad(const std::string& filepath)
    {
        return new OBJ(filepath);
    }

    std::vector<model::Mesh> &OBJ::getMeshes()
    {
        return this->meshes;
    }
}
