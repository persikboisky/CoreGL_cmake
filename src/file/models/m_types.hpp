//
// Created by kisly on 02.12.2025.
//

#ifndef M_TYPES_HPP
#define M_TYPES_HPP

#include <string>
#include <vector>

namespace core::model
{
	enum class TEXTURE_TYPE : int
	{
		DIFFUSE,
		SPECULAR,
		AMBIENT,
		EMISSIVE,
		NORMALS,
		SHININESS,
		OPACITY,
		DISPLACEMENT,
		LIGHTMAP,
		REFLECTION,
		METALNESS,
		DIFFUSE_ROUGHNESS
	};

	struct Vertex
	{
		float x = 0;
		float y = 0;
		float z = 0;
		float nX = 0;
		float nY = 0;
		float nZ = 0;
		float u = 0;
		float v = 0;
	};

	struct Texture
	{
		TEXTURE_TYPE type;
		std::string path;
	};

	struct Mesh
	{
		std::vector <Vertex> vertices = {};
		std::vector <Texture> textures = {};
		std::vector<unsigned int> indices = {};
	};
}

#endif //M_TYPES_HPP