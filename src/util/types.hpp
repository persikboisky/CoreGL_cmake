//
// Created by kisly on 13.07.2025.
//

#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>
#include <vector>
#include "../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#endif //defined(CORE_INCLUDE_VULKAN)

namespace core
{



    namespace model
    {
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

        struct Texture {
            std::string type = "";
            std::string path = "";
        };

        struct Mesh {
            std::vector<Vertex> vertices = {};
            std::vector<Texture> textures = {};
            std::vector<unsigned int> indices = {};
        };
    }
}

#endif //TYPES_HPP
