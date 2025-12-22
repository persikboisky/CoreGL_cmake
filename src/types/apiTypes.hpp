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
	        SHADER_READ,
	        SHADER_WRITE,
	        MEMORY_READ,
	        MEMORY_WRITE,
	        TRANSFER_READ,
            TRANSFER_WRITE
	    };

	    enum class PIPELINE_STAGE : int
	    {
	        NONE,
	        TOP_OF_PIPE,
	        TRANSFER,
	        GEOMETRY_SHADER,
	        VERTEX_INPUT,
	        VERTEX_SHADER,
	        FRAGMENT_SHADER
	    };

	    class Convert
	    {
	    protected:
            friend class GraphicsPipeline;
	        friend class RenderPass;
	        friend class CommandBuffer;
	        friend class ImageView;

	    private:
	        static VkFormat convert(const FORMAT_VARIABLE& format);
	        static VkPrimitiveTopology convert(const vulkan::PRIMITIVE& primitive);
	        static VkPolygonMode convert(const POLYGON_MODE& mode);
	        static VkCullModeFlags convert(const CULL_MODE& mode);
	        static VkFrontFace convert(const FRONT_FACE& face);
	        static VkDynamicState convert(const DYNAMIC_STATE& state);
	        static VkImageLayout convert(const IMAGE_LAYOUT& layout);
	        static VkImageAspectFlags convert(const IMAGE_ASPECT& aspect);
	        static VkAccessFlags convert(const ACCESS& access);
	        static VkPipelineStageFlags convert(const PIPELINE_STAGE& stage);
	    };
	}
#endif //defined(CORE_INCLUDE_VULKAN)

}
#endif //APITYPES_HPP
