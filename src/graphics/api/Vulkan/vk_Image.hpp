//
// Created by kisly on 27.11.2025.
//

#ifndef VK_IMAGE_HPP
#define VK_IMAGE_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../types/apiTypes.hpp"
#include "../../../types/size.hpp"
#include <vulkan/vulkan.h>

namespace core
{
	namespace vulkan
	{
		enum class IMAGE_TYPE : int
		{
			IMG_1D,
			IMG_2D,
			IMG_3D
		};

		enum class IMAGE_FORMAT : int
		{
			B8G8R8_SRGB,
			B8G8R8_UINT,
			B8G8R8A8_SRGB,
			B8G8R8A8_UINT,
			D24_UNORM_S8_UINT,
			D32_SFLOAT
		};

		enum class TYPE_USAGE_IMAGE : int
		{
			TRANSFER_SRC,
			TRANSFER_DST,
			SAMPLED,
			STORAGE,
			COLOR_ATTACHMENT,
			DEPTH_STENCIL_ATTACHMENT
		};

		struct ImageCreateInfo
		{
			class Device* ptrDevice = nullptr;

			Size3i extent = {};
			IMAGE_TYPE image = IMAGE_TYPE::IMG_2D;
			IMAGE_FORMAT format = IMAGE_FORMAT::B8G8R8A8_SRGB;
			TYPE_USAGE_IMAGE usage = TYPE_USAGE_IMAGE::SAMPLED;
			TYPE_MEMORY typeMemory = TYPE_MEMORY::HOST;

			bool exclusiveMode = true;
			uint32_t mipLevels = 1;

			size_t size = 0;
			void* data = nullptr;
		};

		class Image
		{
		protected:
			friend class CommandBuffer;

		private:
			VkDevice* ptrDevice = nullptr;
			VkImage image = nullptr;
			VkDeviceMemory memory = nullptr;

			Image(const ImageCreateInfo& info);

		public:
			~Image();

			static Image create(const ImageCreateInfo& info);
			static Image *ptrCreate(const ImageCreateInfo& info);

			void copy(void* data, uint64_t size);
		};

		class ImageView
		{

		};

		class Texture
		{

		};
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_IMAGE_HPP
