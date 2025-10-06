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
	struct FrameBuffersInfo
	{
		class Device *ptrDevice = nullptr;
		class RenderPass *ptrRenderPass = nullptr;
		class ImageViews *ptrSwapchainImageViews = nullptr;
		class DepthImageViews *ptrDepthImageViews = nullptr;
	};

	class FrameBuffer
	{
	 private:
		VkFramebuffer fbo = {};
		VkDevice* ptrDevice = nullptr;

		FrameBuffer(class Device& device, class RenderPass& renderPass, class ImageView& image, class DepthImageView* ptrDIW);

	 public:
		static FrameBuffer create(
				class Device& device,
				class RenderPass& renderPass,
				class ImageView& image,
				class DepthImageView* ptrDIW = nullptr);

		static FrameBuffer *ptrCreate(
				class Device& device,
				class RenderPass& renderPass,
				class ImageView& image,
				class DepthImageView* ptrDIW = nullptr);

		~FrameBuffer();

		VkFramebuffer getVkFramebuffer();
		VkFramebuffer *getVkPtrFramebuffer();
	};

	class FrameBuffers
	{
	 private:
		std::vector<FrameBuffer*> fbos = {};
		VkDevice *device = nullptr;

		FrameBuffers(FrameBuffersInfo& info);

	 public:
		~FrameBuffers();

		static FrameBuffers create(FrameBuffersInfo& info);

		static FrameBuffers *ptrCreate(FrameBuffersInfo& info);

		std::vector<FrameBuffer*> getPtrFramebuffers();
	};
}

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_FRAMEBUFFER_HPP_
