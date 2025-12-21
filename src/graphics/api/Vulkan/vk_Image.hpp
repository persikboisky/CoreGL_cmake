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
#include <vector>

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

	    enum class IMAGE_USAGE : int
	    {
	        SAMPLED,
	        TRANSFER_DST,
	        TRANSFER_SRC,
	        SAMPLED_TRANSFER_DST,
	        SAMPLED_TRANSFER_SRC,
	    };

        struct ImageCreateInfo
        {
            class Device* ptrDevice = nullptr;
            IMAGE_TYPE type = IMAGE_TYPE::IMG_2D;
            Size3ui extent = {0, 0, 0};
            uint32_t mipLevels = 1;
            IMAGE_FORMAT format = IMAGE_FORMAT::R8G8B8_UNORM;
            IMAGE_USAGE usage = IMAGE_USAGE::SAMPLED;

            /// @brief предназначена ли цепочка показа для одной очереди(использование для одной очереди более производительное)
            bool exclusiveMode = true;

            /// @brief список индексов семейств(нужно если выключен exclusiveMode)
            std::vector<uint32_t> queueFamilyIndices = {};

            uint64_t size = 0;
            void* ptrImageData = nullptr;

            TYPE_MEMORY typeMemory = TYPE_MEMORY::HOST;
        };

	    class Image
	    {
	    protected:
            friend class ImageView;

	    private:
	        VkDevice device = nullptr;
	        VkImage image = nullptr;
	        VkDeviceMemory memory = nullptr;

	        Image(const ImageCreateInfo& info);

	    public:
	        static Image create(const ImageCreateInfo& info);
	        static Image* ptrCreate(const ImageCreateInfo& info);

	        ~Image();

	        void copy(void* data, uint64_t size, uint64_t offset = 0);
	    };

        struct ImageViewCreateInfo
        {
            class Device* ptrDevice = nullptr;
            Image* ptrImage = nullptr;
            IMAGE_FORMAT format = IMAGE_FORMAT::R8G8B8_UNORM;
            IMAGE_TYPE type = IMAGE_TYPE::IMG_2D;
        };

        class ImageView
        {
        protected:
            friend class DescriptorSet;

        private:
            VkDevice device = nullptr;
            VkImageView imageView = nullptr;

            ImageView(const ImageViewCreateInfo& info);

        public:
            static ImageView create(const ImageViewCreateInfo& info);
            static ImageView *ptrCreate(const ImageViewCreateInfo& info);

            ~ImageView();
        };

	    struct SamplerFilter
	    {
	        TEXTURE_FILTER magFilter = TEXTURE_FILTER::LINEAR;
	        TEXTURE_FILTER minFilter = TEXTURE_FILTER::LINEAR;
	    };

	    struct SamplerAddressMode
	    {
            vulkan::TEXTURE_WRAP addressModeU = vulkan::TEXTURE_WRAP::REPEAT;
	        vulkan::TEXTURE_WRAP addressModeV = vulkan::TEXTURE_WRAP::REPEAT;
	        vulkan::TEXTURE_WRAP addressModeW = vulkan::TEXTURE_WRAP::REPEAT;
	    };

	    struct SamplerCreateInfo
	    {
	        class Device* ptrDevice = nullptr;
            SamplerFilter filter = {};
	        SamplerAddressMode addressMode = {};
	    };

	    class Sampler
	    {
	    protected:
	        friend class DescriptorSet;

	    private:
	        VkSampler sampler = nullptr;
	        VkDevice device = nullptr;

            Sampler(const SamplerCreateInfo& info);

	    public:
	        ~Sampler();

	        static Sampler create(const SamplerCreateInfo& info);
	        static Sampler *ptrCreate(const SamplerCreateInfo& info);
	    };
	} // vulkan
} // core

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_IMAGE_HPP
