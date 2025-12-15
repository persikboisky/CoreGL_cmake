//
// Created by kisly on 09.12.2025.
//

#ifndef RENDER_M_FBX_HPP
#define RENDER_M_FBX_HPP

#include <string>
#include <vector>
#include "m_types.hpp"

struct aiMesh;
struct aiScene;
struct aiMaterial;
enum aiTextureType : int;

namespace core
{
	namespace model
	{
		class FBX
		{
		private:
			std::vector<Mesh> meshes = {};

			FBX(const std::string& filepath);

			model::Mesh processMesh(aiMesh* aiMesh, const aiScene* scene);
			static std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, TEXTURE_TYPE typeName);

		public:
			static FBX load(const std::string& filepath);
			static FBX *ptrLoad(const std::string& filepath);

			std::vector<model::Mesh> &getMeshes();
		};
	} // models
} // core

#endif //RENDER_M_FBX_HPP
