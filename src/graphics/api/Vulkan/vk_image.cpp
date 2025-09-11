//
// Created by kisly on 09.09.2025.
//

#include "vk_image.hpp"

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