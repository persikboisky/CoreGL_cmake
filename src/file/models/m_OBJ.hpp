//
// Created by kisly on 27.10.2025.
//

#ifndef M_OBJ_HPP
#define M_OBJ_HPP

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
		class OBJ
		{
		private:
			std::vector<Mesh> meshes = {};

			OBJ(const std::string& filepath);

			model::Mesh processMesh(aiMesh* aiMesh, const aiScene* scene);
			std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

		public:
			static OBJ load(const std::string& filepath);
			static OBJ* ptrLoad(const std::string& filepath);

			std::vector<model::Mesh> &getMeshes();
		};
	}
}

#endif //M_OBJ_HPP
