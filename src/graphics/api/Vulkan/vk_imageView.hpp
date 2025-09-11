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
		 private:
			VkImageView imageView;
			VkDevice* ptrDevice = nullptr;

			ImageView(class Device& device, struct image& img);

		 public:
			static ImageView create(class Device& device, struct image& img);
			static ImageView *ptrCreate(class Device& device, struct image& img);

			~ImageView();

			VkImageView getVkImageView();
			VkImageView *getVkPtrImageView();

//			void operator= (ImageView& image);
		};

		class ImageViews
		{
		 private:
			std::vector<ImageView*> imagesView = {};
			VkDevice* ptrDevice = nullptr;

			ImageViews(class Device& device, class SwapChain& swapChain);
			ImageViews(class Device& device, std::vector<struct image>& img);

		 public:
			~ImageViews();

			static ImageViews create(class Device& device, class SwapChain& swapChain);
			static ImageViews *ptrCreate(class Device& device, class SwapChain& swapChain);

			std::vector<ImageView*> getPtrImagesView();
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_IMAGEVIEW_HPP_
