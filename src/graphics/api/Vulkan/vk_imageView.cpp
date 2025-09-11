//
// Created by kisly on 07.09.2025.
//

#include "vk_imageView.hpp"
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
		ImageView::ImageView(Device& device, image& img) : ptrDevice(device.getPtrDevice())
		{
			VkImageViewCreateInfo viewInfo = {};
			viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			viewInfo.image = img.getVkImage();
			viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			viewInfo.format = device.getVkSurfaceFormat().format;

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
				device.getDevice(),
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

		ImageViews::ImageViews(Device& device, SwapChain& swapChain) : ptrDevice(device.getPtrDevice())
		{
			for (image &img : swapChain.getImages())
			{
				this->imagesView.push_back(ImageView::ptrCreate(device, img));
			}
		}

		ImageViews::ImageViews(Device& device, std::vector<image>& img)
		{
			for (image& cimg : img)
			{
				this->imagesView.push_back(ImageView::ptrCreate(device, cimg));
			}
		}

		ImageViews::~ImageViews()
		{
			for (ImageView* imgVeiw : this->imagesView)
			{
				delete imgVeiw;
			}
			this->imagesView.clear();
		}

		ImageViews ImageViews::create(Device& device, SwapChain& swapChain)
		{
			return ImageViews(device, swapChain);
		}

		ImageViews* ImageViews::ptrCreate(Device& device, SwapChain& swapChain)
		{
			return new ImageViews(device, swapChain);
		}

		std::vector<ImageView*> ImageViews::getPtrImagesView()
		{
			return this->imagesView;
		}



	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
