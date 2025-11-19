//
// Created by kisly on 05.09.2025.
//

#ifndef VK_FRAMEBUFFER_HPP
#define VK_FRAMEBUFFER_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#include <vector>

namespace core
{
	namespace vulkan
	{
		struct FrameBufferInfo
		{
			class Device* ptrDevice = nullptr;
			class RenderPass* ptrRenderPass = nullptr;
			uint32_t width = 600;
			uint32_t height = 600;
			bool flagDepthStencilAttachment = false;
		};

		class FrameBuffer
		{
		protected:
			friend class CommandBuffer;

		private:
			VkFramebuffer* frameBuffers = nullptr;
//			VkImageView* colorImagesView = nullptr;
//			VkImage* colorImages = nullptr;
//   		VkDeviceMemory* colorImageMemory = nullptr;
			VkImage* depthImages = nullptr;
			VkImageView* depthImagesView = nullptr;
			VkDeviceMemory* depthImageMemory = nullptr;
			uint32_t count = 0;

			VkDevice* ptrDevice = nullptr;

//			FrameBuffer(const FrameBufferInfo& info, uint32_t countImage);
			FrameBuffer(const FrameBufferInfo& info, const class SwapChain& ptrSwapChain);

		public:
			~FrameBuffer();

//			static FrameBuffer create(const FrameBufferInfo& info, uint32_t countImage);
			static FrameBuffer create(const FrameBufferInfo& info, const class SwapChain& swapChain);
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_FRAMEBUFFER_HPP
