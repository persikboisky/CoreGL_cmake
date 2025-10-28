//
// Created by kisly on 09.09.2025.
//

#include "vk_image.hpp"

#if defined(CORE_INCLUDE_VULKAN)

namespace core
{
	namespace vulkan
	{
		image::image(VkImage& image) : objImage(image)
		{
		}

		void image::operator=(VkImage& image)
		{
			this->objImage = image;
		}

		VkImage image::getVkImage()
		{
			return this->objImage;
		}

		VkImage* image::getVkPtrImage()
		{
			return &this->objImage;
		}
	} // vulkan
} // core

#endif // defined(CORE_INCLUDE_VULKAN)
