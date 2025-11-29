//
// Created by kisly on 27.11.2025.
//

#ifndef VK_IMAGE_HPP
#define VK_IMAGE_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../util/types.hpp"
#include "../../../types/size.hpp"
#include <vulkan/vulkan.h>

namespace core
{
	namespace vulkan
	{
		enum class IMAGE_TYPE : int
		{
			IMG_1D,
			IMG_2D,
			IMG_3D
		};

		struct ImageCreateinfo
		{
			Size3i extent = {};
			IMAGE_TYPE imageType = IMAGE_TYPE::IMG_2D;
			bool exclusiveMode = true;
		};

		class Image
		{
		private:
			VkImage image = nullptr;

			Image(const ImageCreateinfo& info);
		};

		class ImageView
		{

		};

		class Texture
		{

		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_IMAGE_HPP
