//
// Created by kisly on 29.11.2025.
//

#ifndef APITYPES_HPP
#define APITYPES_HPP

#include "../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include <vulkan/vulkan.h>
#endif //defined(CORE_INCLUDE_VULKAN)

namespace core
{
	struct Version2
	{
		int MAJOR;
		int MINOR;

		Version2(int MAJOR, int MINOR) : MINOR(MINOR), MAJOR(MAJOR)
		{
		}

		void operator=(const Version2& v2)
		{
			this->MINOR = v2.MINOR;
			this->MAJOR = v2.MAJOR;
		}
	};
	struct Version3
	{
		int MAJOR;
		int MINOR;
		int PATCH;

		Version3(int MAJOR, int MINOR, int PATCH) : MINOR(MINOR), MAJOR(MAJOR), PATCH(PATCH)
		{
		}

		void operator=(const Version3& v3)
		{
			this->MINOR = v3.MINOR;
			this->MAJOR = v3.MAJOR;
			this->PATCH = v3.PATCH;
		}
	};
	struct Viewport
	{
		float x = 0;
		float y = 0;
		float width = 0;
		float height = 0;
		float minDepth = 0;
		float maxDepth = 1;
	};
	struct Rect2D
	{
		int x;
		int y;
		int width;
		int height;
	};

	enum class PRIMITIVE : int
	{
		POINTS,
		LINES,
		LINE_STRIP,
		LINE_LOOP,
		TRIANGLES,
		TRIANGLES_FAN,
		TRIANGLES_STRIP
	};
	enum class TYPE_SHADER : int
	{
		FRAGMENT,
		GEOMETRY,
		VERTEX,
	    COMPUTER
	};
	enum class CULL_MODE : int
	{
		BACK,
		FRONT,
		FRONT_AND_BACK,
		NONE
	};
	enum class FRONT_FACE : int
	{
		COUNTER_CLOCKWISE,
		CLOCKWISE
	};
	enum class TYPE_WRAPPING_TEXTURE : int
	{
		REPEAT,
		MIRRORED_REPEAT,
		CLAMP_TP_EDGE,
		CLAMP_TO_BORDER
	};
	enum class POLYGON_MODE : int
	{
		POINT,
		LINE,
		FILL
	};
	enum class POLYGON : int
	{
		FRONT,
		BACK,
		FRONT_AND_BACK
	};
	enum class TYPES_COORD : int
	{
		POSITIVE_RELATIVE,
		RELATIVE,
		POSITIVE_WINDOW,
		WINDOW
	};
	enum class BUFFER : int
	{
		COLOR = 1,
		DEPTH = 2,
		NONE = 0
	};
	enum class TYPE : int
	{
		INT,
		UNSIGNED_INT,
		FLOAT,
		DOUBLE,
	};
	enum class FILTER : int
	{
		NEAREST,
		LINEAR,
		CUBIC_EXT
	};
	enum class MIPMAP_MODE : int {
		NEAREST,
		LINEAR
	};
	enum class ADDRESS_MODE : int
	{
		REPEAT,
		MIRRORED_REPEAT,
		CLAMP_TO_EDGE,
		CLAMP_TO_BORDER,
		MIRROR_CLAMP_TO_EDGE
	};
	enum class BORDER_COLOR : int
	{
		FLOAT_TRANSPARENT_BLACK,
		INT_TRANSPARENT_BLACK,
		FLOAT_OPAQUE_BLACK,
		INT_OPAQUE_BLACK,
		FLOAT_OPAQUE_WHITE,
		INT_OPAQUE_WHITE
	};
    enum class TEXTURE_WRAP : int
    {
        REPEAT,
        CLAMP_TO_EDGE,
        CLAMP_TO_BORDER,
        MIRRORED_REPEAT,
        MIRROR_CLAMP_TO_BORDER
    };
    enum class TEXTURE_FILTER : int
    {
        NEAREST,
        LINEAR,
        NEAREST_MIPMAP_NEAREST,
        LINEAR_MIPMAP_NEAREST,
        NEAREST_MIPMAP_LINEAR,
        LINEAR_MIPMAP_LINEAR
    };
    enum class INDEX_TYPE : unsigned int
    {
        UINT8,
        UINT16,
        UINT32
    };

    namespace opengl
    {
        enum class IMAGE_INTERNAL_FORMAT : unsigned int
        {
            R8,
            R16,
            R16F,
            R32F,
            RG8,
            RG16,
            RG16F,
            RG32F,
            RGB8,
            RGB16,
            RGB16F,
            RGB32F,
            RGBA8,
            RGBA16,
            RGBA16F,
            RGBA32F,
            DEPTH_COMPONENT16,
            DEPTH_COMPONENT24,
            DEPTH24_STENCIL8,
            DEPTH32F_STENCIL8
        };
        enum class IMAGE_FORMAT : unsigned int
        {
            RED,
            GREEN,
            BLUE,
            RG,
            RGB,
            BGR,
            RGBA,
            BGRA,
            ALPHA,
            DEPTH_COMPONENT,
            DEPTH_STENCIL
        };
        enum class IMAGE_TYPE : unsigned int {
            UNSIGNED_BYTE,
            FLOAT
        };

        class Convert
        {
        protected:
            friend class VertexBuffer;
            friend class Texture;

        private:
            static int convert(const TYPE& type);
            static unsigned int convertSizeType(const TYPE& type);
            static int convertAndAlignment(const IMAGE_INTERNAL_FORMAT& format);
            static unsigned int convert(const IMAGE_FORMAT& format);
        };
    }


#if defined(CORE_INCLUDE_VULKAN)
	namespace vulkan
	{
		enum PRIMITIVE : int
		{
			POINT_LIST,
			LINE_LIST,
			LINE_STRIP,
			TRIANGLE_LIST,
			TRIANGLE_STRIP,
			TRIANGLE_FAN
		};
		enum SHADER_STAGES : int
		{
			VERTEX_STAGE,
			FRAGMENT_STAGE,
			GEOMETRY_STAGE,
			VERTEX_FRAGMENT_STAGES,
			VERTEX_GEOMETRY_FRAGMENT_STAGES,
			ALL_STAGES
		};
		enum FORMAT_VARIABLE : int
		{
			FLOAT,
			VEC2,
			VEC3,
			VEC4,
			UINT,
			INT
		};
		enum class DYNAMIC_STATE : int
		{
			CULL_MODE,
			SCISSOR,
			PRIMITIVE_TOPOLOGY
		};
		enum class TYPE_MEMORY : int
		{
			DEVICE_LOCAL,
			HOST
		};
	    enum class IMAGE_FORMAT : int
        {
            R8G8B8A8_UNORM,
            B8G8R8A8_UNORM,
            R8G8B8A8_SRGB,
            R8G8B8_UNORM,
            R8G8B8_SRGB,
            R16G16B16A16_SFLOAT,
            R16G16_SFLOAT,
            R16_SFLOAT,
            R32G32B32A32_SFLOAT,
            R32G32B32_SFLOAT,
            D32_SFLOAT,
            D24_UNORM_S8_UINT,
            D32_SFLOAT_S8_UINT,
            D16_UNORM,
            A8_UNORM,
        };
	    enum class TEXTURE_FILTER : int
	    {
	        NEAREST,
	        LINEAR,
	        CUBIC_EXT,
	        CUBIC_IMG
	    };
	    enum class TEXTURE_WRAP : int
        {
            REPEAT,
            CLAMP_TO_EDGE,
            CLAMP_TO_BORDER,
            MIRRORED_REPEAT
        };
        enum class IMAGE_LAYOUT : int
	    {
	        UNDEFINED,
	        GENERAL,
	        TRANSFER_SRC_OPTIMAL,
	        TRANSFER_DST_OPTIMAL,
	        SHADER_READ_ONLY_OPTIMAL,
	        COLOR_ATTACHMENT_OPTIMAL,
	        DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
	        PRESENT_SRC_KHR
	    };
        enum class LOAD_OP : int
        {
            LOAD_OP_CLEAR,
            LOAD_OP_LOAD,
            LOAD_OP_DONT_CARE
        };
        enum class STORE_OP : int
        {
            STORE_OP_STORE,
            STORE_OP_DONT_CARE
        };
	    enum class IMAGE_ASPECT : int
	    {
	        COLOR,
	        DEPTH,
	        STENCIL,
	        DEPTH_STENCIL
	    };

	    enum class ACCESS : int
	    {
	        NONE,
	        // Чтение
            INDIRECT_COMMAND_READ,          // Чтение indirect buffers
            VERTEX_ATTRIBUTE_READ,          // Чтение вершинных буферов
            UNIFORM_READ,                   // Чтение uniform buffers
            INPUT_ATTACHMENT_READ,          // Чтение input attachments
            SHADER_READ,                    // Чтение в шейдере (текстуры)
            COLOR_ATTACHMENT_READ,          // Чтение из color attachment
            DEPTH_STENCIL_ATTACHMENT_READ,  // Чтение глубины/трафарета

            // Запись
            SHADER_WRITE_BIT,                   // Запись в шейдере (SSBO, image)
            COLOR_ATTACHMENT_WRITE,         // Запись в color attachment
            DEPTH_STENCIL_ATTACHMENT_WRITE, // Запись глубины/трафарета
            TRANSFER_WRITE,                 // Запись при копировании

            // Комбинированные
            COLOR_ATTACHMENT_READ_WRITE,    // Чтение+запись color attachment
            DEPTH_STENCIL_ATTACHMENT_READ_WRITE, // Чтение+запись глубины
            MEMORY_READ,                    // Любое чтение из памяти
            MEMORY_WRITE,                   // Любая запись в память
	    };

	    enum class PIPELINE_STAGE : int
	    {
            NONE,

	        // Ранние стадии (вершинный пайплайн)
	        TOP_OF_PIPE,        // Самое начало
            DRAW_INDIRECT,      // Чтение indirect buffers
            VERTEX_INPUT,       // Чтение вершинных буферов
            VERTEX_SHADER,     // Вершинный шейдер
            TESSELLATION_CONTROL_SHADER,
            TESSELLATION_EVALUATION_SHADER,
            GEOMETRY_SHADER,

            // Фрагментный пайплайн
            FRAGMENT_SHADER,   // Фрагментный шейдер
            EARLY_FRAGMENT_TESTS,// Ранние тесты глубины/трафарета
            LATE_FRAGMENT_TESTS, // Поздние тесты глубины/трафарета
            COLOR_ATTACHMENT_OUTPUT,// Запись в color attachment

            // Поздние стадии
            BOTTOM_OF_PIPE,     // Самое окончание
            TRANSFER,           // Копирование данных
            COMPUTE_SHADER,     // Вычислительный шейдер

            // Сокращения (битовые маски нескольких стадий)
            ALL_GRAPHICS,       // Все графические стадии
            ALL_COMMANDS,       // Все стадии
	    };

        enum class PIPELINE_BIND_POINT : int
        {
            GRAPHICS,
            COMPUTER
        };

        enum class SAMPLES : int
        {
            _1BIT,
            _2BIT,
            _4BIT,
            _8BIT,
            _16BIT,
            _32BIT,
            _64BIT
        };

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
            DEPTH_STENCIL_ATTACHMENT
        };

        enum class DESCRIPTOR_TYPE : int
        {
            UNIFORM_BUFFER,
            UNIFORM_BUFFER_DYNAMIC,
            COMBINED_IMAGE_SAMPLER
        };

	    class Convert
	    {
	    protected:
            friend class GraphicsPipeline;
	        friend class RenderPass;
	        friend class CommandBuffer;
	        friend class ImageView;
	        friend class Image;
	        friend class PhysicalDeviceInfo;
	        friend class SwapChain;
	        friend class DescriptorPool;
	        friend class DescriptorSetLayout;

	    private:
	        static VkFormat convert(const FORMAT_VARIABLE& format);
	        static VkFormat convert(const IMAGE_FORMAT& format);
	        static VkPrimitiveTopology convert(const PRIMITIVE& primitive);
	        static VkPolygonMode convert(const POLYGON_MODE& mode);
	        static VkCullModeFlags convert(const CULL_MODE& mode);
	        static VkFrontFace convert(const FRONT_FACE& face);
	        static VkDynamicState convert(const DYNAMIC_STATE& state);
	        static VkImageLayout convert(const IMAGE_LAYOUT& layout);
	        static VkImageAspectFlags convert(const IMAGE_ASPECT& aspect);
	        static VkAccessFlags convert(const ACCESS& access);
	        static VkPipelineStageFlags convert(const PIPELINE_STAGE& stage);
	        static VkIndexType convert(const INDEX_TYPE& type);
	        static VkAttachmentLoadOp convert(const LOAD_OP& op);
	        static VkAttachmentStoreOp convert(const STORE_OP& op);
	        static VkSampleCountFlagBits convert(const SAMPLES& samples);
	        static VkPipelineBindPoint convert(const PIPELINE_BIND_POINT& bind_point);
	        static VkImageUsageFlags convert(const IMAGE_USAGE& usage);
	        static VkDescriptorType convert(const DESCRIPTOR_TYPE& type);
	    };
	}
#endif //defined(CORE_INCLUDE_VULKAN)

}
#endif //APITYPES_HPP
