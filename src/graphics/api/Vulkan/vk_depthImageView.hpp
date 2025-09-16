//
// Created by kisly on 16.09.2025.
//

#ifndef VK_DEPTHIMAGEVIEW_HPP
#define VK_DEPTHIMAGEVIEW_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include <vector>

namespace core::vulkan
{
	class DepthImageView
	{
	private:
		VkImage depthImage;
		VkDeviceMemory depthImageMemory;
		VkImageView depthImageView;
		VkDevice* ptrDevice = nullptr;

		explicit DepthImageView(class Device& device);

	public:
		~DepthImageView();

		static DepthImageView create(class Device& device);
		static DepthImageView *ptrCreate(class Device& device);

		VkImageView getVkImageView();
		VkImageView *getVkPtrImageView();
	};

	class DepthImageViews
	{
	private:
		std::vector<DepthImageView*> ptrImageViews = {};

		DepthImageViews(class Device& device, class SwapChain& swapChain);

	public:
		~DepthImageViews();

		static DepthImageViews create(class Device& device, class SwapChain& swapChain);
		static DepthImageViews *ptrCreate(class Device& device, class SwapChain& swapChain);

		std::vector<DepthImageView*> getDepthImageViewsPtr();
	};
}

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_DEPTHIMAGEVIEW_HPP
