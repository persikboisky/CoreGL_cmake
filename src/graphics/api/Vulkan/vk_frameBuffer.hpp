//
// Created by kisly on 07.09.2025.
//

#ifndef VK_FRAMEBUFFER_HPP_
#define VK_FRAMEBUFFER_HPP_

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include <vector>

namespace core::vulkan
{
	class FrameBuffer
	{
	 private:
		VkFramebuffer fbo = {};
		VkDevice* ptrDevice = nullptr;

		FrameBuffer(class Device& device, class RenderPass& renderPass, class ImageView& image);

	 public:
		static FrameBuffer create(class Device& device, class RenderPass& renderPass, class ImageView& image);
		static FrameBuffer *ptrCreate(class Device& device, class RenderPass& renderPass, class ImageView& image);

		~FrameBuffer();

		VkFramebuffer getVkFramebuffer();
		VkFramebuffer *getVkPtrFramebuffer();
	};

	class FrameBuffers
	{
	 private:
		std::vector<FrameBuffer*> fbos = {};
		VkDevice *device = nullptr;

		FrameBuffers(class Device& device, class RenderPass& renderPass, class ImageViews& swapchainImageViews);

	 public:
		~FrameBuffers();

		static FrameBuffers create(class Device& device, class RenderPass& renderPass, class ImageViews& swapchainImageViews);
		static FrameBuffers *ptrCreate(class Device& device, class RenderPass& renderPass, class ImageViews& swapchainImageViews);

		std::vector<FrameBuffer*> getPtrFramebuffers();
	};
}

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_FRAMEBUFFER_HPP_
