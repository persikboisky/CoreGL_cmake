//
// Created by kisly on 09.09.2025.
//

#ifndef VK_IMAGE_HPP_
#define VK_IMAGE_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>

namespace core
{
	namespace vulkan
	{
		struct image final
		{
		 private:
			VkImage objImage;

		 public:
			image(VkImage& image);

			void operator=(VkImage& image);

			VkImage getVkImage();
			VkImage *getVkPtrImage();
		};

		class Image
		{

		};

		class Images
		{

		};

	} // vulkan
} // core

#endif // defined(CORE_INCLUDE_VULKAN)
#endif //VK_IMAGE_HPP_
