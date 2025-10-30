//
// Created by kisly on 07.09.2025.
//

#include "vk_SwapChainImageView.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_swapChain.hpp"
#include "vk_device.hpp"
#include "vk_image.hpp"
#include "../../../util/coders.hpp"
#include <iostream>

namespace core
{
	namespace vulkan
	{
		ImageView::ImageView(Device& device, image& img) : ptrDevice(&device.device)
		{
			VkImageViewCreateInfo viewInfo = {};
			viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			viewInfo.image = img.getVkImage();
			viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			viewInfo.format = device.surfaceFormat.format;

			// Компоненты - можно делать swizzle (переназначать каналы)
			viewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			viewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			viewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			viewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

			// Subresource range - какая часть изображения используется
			viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			viewInfo.subresourceRange.baseMipLevel = 0; // Начинаем с 0-го уровня мипмаппинга
			viewInfo.subresourceRange.levelCount = 1; // Сколько уровней мипмаппинга использовать
			viewInfo.subresourceRange.baseArrayLayer = 0; // Начинаем с 0-го слоя
			viewInfo.subresourceRange.layerCount = 1; // Сколько слоев использовать (1 для 2D текстур)

			VkResult result = vkCreateImageView(
				device.device,
				&viewInfo,
				nullptr,
				&this->imageView);
			coders::vulkanProcessingError(result);
		}

		ImageView ImageView::create(Device& device, image& img)
		{
			return ImageView(device, img);
		}

		VkImageView *ImageView::getVkPtrImageView()
		{
			return &this->imageView;
		}

		ImageView* ImageView::ptrCreate(Device& device, image& img)
		{
			return new ImageView(device, img);
		}

		ImageView::~ImageView()
		{
			vkDestroyImageView(
				*this->ptrDevice,
				this->imageView,
				nullptr);
		}

		VkImageView ImageView::getVkImageView()
		{
			return this->imageView;
		}

//		void ImageView::operator=(ImageView& image)
//		{
//			this->imageView = image.getVkImageView();
//		}

		SwapchainImagesView::SwapchainImagesView(Device& device, SwapChain& swapChain) : ptrDevice(&device.device)
		{
			for (image &img : swapChain.getImages())
			{
				this->imagesView.push_back(ImageView::ptrCreate(device, img));
			}
		}

		SwapchainImagesView::SwapchainImagesView(Device& device, std::vector<image>& img)
		{
			for (image& cimg : img)
			{
				this->imagesView.push_back(ImageView::ptrCreate(device, cimg));
			}
		}

		SwapchainImagesView::~SwapchainImagesView()
		{
			for (ImageView* imgView : this->imagesView)
			{
				delete imgView;
			}
			this->imagesView.clear();
		}

		SwapchainImagesView SwapchainImagesView::create(Device& device, SwapChain& swapChain)
		{
			return SwapchainImagesView(device, swapChain);
		}

		SwapchainImagesView* SwapchainImagesView::ptrCreate(Device& device, SwapChain& swapChain)
		{
			return new SwapchainImagesView(device, swapChain);
		}

		std::vector<ImageView*> SwapchainImagesView::getPtrImagesView()
		{
			return this->imagesView;
		}
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
