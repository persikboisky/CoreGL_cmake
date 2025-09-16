//
// Created by kisly on 16.09.2025.
//

#include "vk_depthImageView.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_device.hpp"
#include "vk_swapChain.hpp"
#include "../../../util/coders.hpp"

namespace core::vulkan
{
	DepthImageView::DepthImageView(Device& device) : ptrDevice(device.getPtrDevice())
	{
		VkImageCreateInfo imageInfo{};
		imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		imageInfo.imageType = VK_IMAGE_TYPE_2D;
		imageInfo.format = VK_FORMAT_D32_SFLOAT;
		imageInfo.extent.depth = 1.0;
		imageInfo.extent.width = device.getVkSurfaceCapabilities().currentExtent.width;
		imageInfo.extent.height = device.getVkSurfaceCapabilities().currentExtent.height;
		imageInfo.mipLevels = 1;
		imageInfo.arrayLayers = 1;
		imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
		imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
		imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
		imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

		VkResult result = vkCreateImage(
				device.getDevice(),
				&imageInfo,
				nullptr,
				&this->depthImage);
		coders::vulkanProcessingError(result);

		VkMemoryRequirements memRequirements;
		vkGetImageMemoryRequirements(device.getDevice(), depthImage, &memRequirements);

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = device.findMemoryType(
				memRequirements.memoryTypeBits,
				VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

		result = vkAllocateMemory(
				device.getDevice(),
				&allocInfo,
				nullptr,
				&this->depthImageMemory);
		coders::vulkanProcessingError(result);
		result = vkBindImageMemory(
				device.getDevice(),
				depthImage,
				this->depthImageMemory,
				0);
		coders::vulkanProcessingError(result);

		VkImageViewCreateInfo viewInfo{};
		viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		viewInfo.image = depthImage;
		viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		viewInfo.format = VK_FORMAT_D32_SFLOAT;
		viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
		viewInfo.subresourceRange.baseMipLevel = 0;
		viewInfo.subresourceRange.levelCount = 1;
		viewInfo.subresourceRange.baseArrayLayer = 0;
		viewInfo.subresourceRange.layerCount = 1;

		result = vkCreateImageView(
				device.getDevice(),
				&viewInfo,
				nullptr,
				&this->depthImageView);
		coders::vulkanProcessingError(result);
	}

	DepthImageView::~DepthImageView()
	{
		vkDestroyImageView(*this->ptrDevice, this->depthImageView, nullptr);
		vkFreeMemory(*this->ptrDevice, this->depthImageMemory, nullptr);
		vkDestroyImage(*this->ptrDevice, this->depthImage, nullptr);
	}

	DepthImageView DepthImageView::create(Device& device)
	{
		return DepthImageView(device);
	}

	DepthImageView* DepthImageView::ptrCreate(Device& device)
	{
		return new DepthImageView(device);
	}

	VkImageView DepthImageView::getVkImageView()
	{
		return this->depthImageView;
	}

	VkImageView* DepthImageView::getVkPtrImageView()
	{
		return &this->depthImageView;
	}

	DepthImageViews::DepthImageViews(Device& device, SwapChain& swapChain)
	{
		for (uint32_t i = 0; i < swapChain.getCountImage(); i++)
		{
			this->ptrImageViews.push_back(DepthImageView::ptrCreate(device));
		}
	}

	DepthImageViews::~DepthImageViews()
	{
		for (DepthImageView* obj : this->ptrImageViews)
		{
			delete obj;
		}
	}

	DepthImageViews DepthImageViews::create(Device& device, SwapChain& swapChain)
	{
		return DepthImageViews(device, swapChain);
	}

	DepthImageViews* DepthImageViews::ptrCreate(Device& device, SwapChain& swapChain)
	{
		return new DepthImageViews(device, swapChain);
	}

	std::vector<DepthImageView*> DepthImageViews::getDepthImageViewsPtr()
	{
		return this->ptrImageViews;
	}
}

#endif //defined(CORE_INCLUDE_VULKAN)

