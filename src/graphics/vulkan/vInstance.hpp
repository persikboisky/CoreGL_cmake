//
// Created by kisly on 03.08.2025.
//

#ifndef VINSTANCE_HPP
#define VINSTANCE_HPP

#include <vulkan/vulkan.h>

namespace core
{
    namespace vulkan
    {
        struct instanceInfo
        {
            unsigned int VULKAN_VERSION_MAJOR = 1;
            unsigned int VULKAN_VERSION_MINOR = 4;
            unsigned int VULKAN_VERSION_PATCH = 0;
            const char* applicationName = "CoreGL";
            bool glfw = true;
        };

        class Instance
        {
        private:
            VkInstance instance;

            Instance(const instanceInfo& instInfo);

        public:
            static Instance create(const instanceInfo& instInfo = {});
            static Instance *ptrCreate(const instanceInfo& instInfo = {});

            ~Instance();
        };
    }
} // core

#endif //VINSTANCE_HPP
