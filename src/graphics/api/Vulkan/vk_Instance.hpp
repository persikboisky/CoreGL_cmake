//
// Created by kisly on 01.09.2025.
//

#ifndef VK_INSTANCE_HPP_
#define VK_INSTANCE_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../util/types.hpp"
#include <vulkan/vulkan.h>

namespace core
{
	namespace vulkan
	{
		struct instanceInfo
		{
			version3 VULKAN_API_VERSION = {1, 2, 0};
			version3 APP_VERSION = {1, 4, 0};
			const char* APP_NAME = "CoreGL";
			bool debugApiDump = false;
		};

		class Instance
		{
		 private:
			VkInstance  instance{};

			explicit Instance(const instanceInfo& info);

		 public:
			static Instance create(const instanceInfo& info = {});
			static Instance *PtrCreate(const instanceInfo& info = {});

			~Instance();

			[[maybe_unused]] VkInstance getVkInstance();
			[[maybe_unused]] VkInstance *getVkPtrInstance();
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_INSTANCE_HPP_



