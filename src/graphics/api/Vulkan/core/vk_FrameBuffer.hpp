//
// Created by kisly on 05.09.2025.
//

#ifndef VK_FRAMEBUFFER_HPP
#define VK_FRAMEBUFFER_HPP

#include "../../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "vk_Image.hpp"

#include <vector>
#include <vulkan/vulkan.h>

namespace core
{
	namespace vulkan
	{
		struct FrameBufferInfo
		{
			class Device* ptrDevice = nullptr;
			class RenderPass* ptrRenderPass = nullptr;
		    std::vector<ImageView*> vecPtrImageViews = {};
			uint32_t width = 600;
			uint32_t height = 600;
		};

		class FrameBuffer
		{
		protected:
			friend class CommandBuffer;

		private:
			VkFramebuffer frameBuffer = nullptr;
			VkDevice* ptrDevice = nullptr;

			FrameBuffer(const FrameBufferInfo& info);

		public:
			~FrameBuffer();

			static FrameBuffer create(const FrameBufferInfo& info);
		    static FrameBuffer* ptrCreate(const FrameBufferInfo& info);
		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_FRAMEBUFFER_HPP
