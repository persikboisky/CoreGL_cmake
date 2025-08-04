//
// Created by kisly on 03.08.2025.
//

#ifndef VINSTANCE_HPP
#define VINSTANCE_HPP

#include "../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../util/types.hpp"
#include <vulkan/vulkan.h>

namespace core
{
    namespace vulkan
    {
        struct InstanceInfo
        {
            const char* appName = "CoreGL";
            version3 appVersion = {1, 0, 0};
            version3 vulkanVersion = {1, 4, 0};
            bool glfw = true;
        };

        class Instance
        {
        private:
            VkInstance instance;

            Instance(const InstanceInfo& instInfo);

        public:
            ~Instance();

            static Instance create(const InstanceInfo& instInfo = {});
            static Instance *ptrCreate(const InstanceInfo& instInfo = {});

            VkInstance getVkInstance();
        };
    }
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VINSTANCE_HPP
