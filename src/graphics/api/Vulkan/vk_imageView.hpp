//
// Created by kisly on 07.09.2025.
//

#ifndef VK_IMAGEVIEW_HPP_
#define VK_IMAGEVIEW_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include <vector>

namespace core
{
	namespace vulkan
	{
		class ImageView
		{

		};

		class ImageViews
		{
		 private:
			std::vector<VkImageView> image = {};
			VkDevice* ptrDevice = nullptr;

			ImageViews(class Device& device, class SwapChain& swapChain);

		 public:
			~ImageViews();

			static ImageViews create(class Device& device, class SwapChain& swapChain);
			static ImageViews *ptrCreate(class Device& device, class SwapChain& swapChain);
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_IMAGEVIEW_HPP_
