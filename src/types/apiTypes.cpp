//
// Created by kisly on 29.11.2025.
//

#include "apiTypes.hpp"
#include <GL/glew.h>
#if defined(CORE_INCLUDE_VULKAN)

namespace core::vulkan
{
VkFormat Convert::convert(const core::vulkan::FORMAT_VARIABLE& format)
{
    switch (format)
    {
    case vulkan::FLOAT:
        return VK_FORMAT_R32_SFLOAT;
    case vulkan::INT:
        return VK_FORMAT_R32_SINT;
    case vulkan::UINT:
        return VK_FORMAT_R32_UINT;
    case vulkan::VEC2:
        return VK_FORMAT_R32G32_SFLOAT;
    case vulkan::VEC3:
        return VK_FORMAT_R32G32B32_SFLOAT;
    case vulkan::VEC4:
        return VK_FORMAT_R32G32B32A32_SFLOAT;
    default:
        return VK_FORMAT_R32_SFLOAT;
    }
}

VkFormat Convert::convert(const IMAGE_FORMAT &format)
{
    switch (format)
    {
    case IMAGE_FORMAT::R8G8B8A8_UNORM:
        return VK_FORMAT_R8G8B8A8_UNORM;
    case IMAGE_FORMAT::R8G8B8_SRGB:
        return VK_FORMAT_R8G8B8_SRGB;
    case IMAGE_FORMAT::R8G8B8A8_SRGB:
        return VK_FORMAT_R8G8B8A8_SRGB;
    case IMAGE_FORMAT::R8G8B8_UNORM:
        return VK_FORMAT_R8G8B8_UNORM;
    case IMAGE_FORMAT::B8G8R8A8_UNORM:
        return VK_FORMAT_B8G8R8A8_UNORM;
    case IMAGE_FORMAT::D16_UNORM:
        return VK_FORMAT_D16_UNORM;
    case IMAGE_FORMAT::D24_UNORM_S8_UINT:
        return VK_FORMAT_D24_UNORM_S8_UINT;
    case IMAGE_FORMAT::A8_UNORM:
        return VK_FORMAT_A8_UNORM;
    case IMAGE_FORMAT::D32_SFLOAT:
        return VK_FORMAT_D32_SFLOAT;
    case IMAGE_FORMAT::D32_SFLOAT_S8_UINT:
        return VK_FORMAT_D32_SFLOAT_S8_UINT;
    case IMAGE_FORMAT::R16G16B16A16_SFLOAT:
        return VK_FORMAT_R16G16B16A16_SFLOAT;
    case IMAGE_FORMAT::R16_SFLOAT:
        return VK_FORMAT_R16_SFLOAT;
    case IMAGE_FORMAT::R16G16_SFLOAT:
        return VK_FORMAT_R16G16_SFLOAT;
    case IMAGE_FORMAT::R32G32B32_SFLOAT:
        return VK_FORMAT_R32G32B32_SFLOAT;
    case IMAGE_FORMAT::R32G32B32A32_SFLOAT:
    default:
        return VK_FORMAT_R32G32B32A32_SFLOAT;
    }
}

VkPrimitiveTopology Convert::convert(const vulkan::PRIMITIVE &primitive)
{
    switch (primitive)
    {
    case TRIANGLE_STRIP:
        return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
    case TRIANGLE_LIST:
        return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    case TRIANGLE_FAN:
        return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
    case LINE_STRIP:
        return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
    case POINT_LIST:
        return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
    default:
        return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
    }
}

VkPolygonMode Convert::convert(const POLYGON_MODE &mode)
{
    switch (mode)
    {
    case POLYGON_MODE::FILL:
        return VK_POLYGON_MODE_FILL;
    case POLYGON_MODE::LINE:
        return VK_POLYGON_MODE_LINE;
    case POLYGON_MODE::POINT:
    default:
        return VK_POLYGON_MODE_POINT;
    }
}

VkCullModeFlags Convert::convert(const CULL_MODE &mode)
{
    switch (mode)
    {
    case CULL_MODE::BACK:
        return VK_CULL_MODE_BACK_BIT;
    case CULL_MODE::FRONT:
        return VK_CULL_MODE_FRONT_BIT;
    case CULL_MODE::FRONT_AND_BACK:
        return VK_CULL_MODE_FRONT_AND_BACK;
    case CULL_MODE::NONE:
    default:
        return VK_CULL_MODE_NONE;
    }
}

VkFrontFace Convert::convert(const FRONT_FACE &face)
{
    return face == FRONT_FACE::COUNTER_CLOCKWISE ? VK_FRONT_FACE_COUNTER_CLOCKWISE : VK_FRONT_FACE_CLOCKWISE;
}

VkDynamicState Convert::convert(const DYNAMIC_STATE &state)
{
    switch (state)
    {
    case DYNAMIC_STATE::CULL_MODE:
        return VK_DYNAMIC_STATE_CULL_MODE;
    case DYNAMIC_STATE::PRIMITIVE_TOPOLOGY:
        return VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY;
    case DYNAMIC_STATE::SCISSOR:
    default:
        return VK_DYNAMIC_STATE_SCISSOR;
    }
}

VkImageLayout Convert::convert(const IMAGE_LAYOUT &layout)
{
    switch (layout)
    {
    case IMAGE_LAYOUT::UNDEFINED:
        return VK_IMAGE_LAYOUT_UNDEFINED;
    case IMAGE_LAYOUT::COLOR_ATTACHMENT_OPTIMAL:
        return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    case IMAGE_LAYOUT::DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
        return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    case IMAGE_LAYOUT::GENERAL:
        return VK_IMAGE_LAYOUT_GENERAL;
    case IMAGE_LAYOUT::PRESENT_SRC_KHR:
        return VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    case IMAGE_LAYOUT::SHADER_READ_ONLY_OPTIMAL:
        return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    case IMAGE_LAYOUT::TRANSFER_DST_OPTIMAL:
        return VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    case IMAGE_LAYOUT::TRANSFER_SRC_OPTIMAL:
    default:
        return VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    }
}

VkImageAspectFlags Convert::convert(const IMAGE_ASPECT &aspect)
{
    switch (aspect)
    {
    case IMAGE_ASPECT::COLOR:
        return VK_IMAGE_ASPECT_COLOR_BIT;
    case IMAGE_ASPECT::DEPTH:
        return VK_IMAGE_ASPECT_DEPTH_BIT;
    case IMAGE_ASPECT::STENCIL:
        return VK_IMAGE_ASPECT_STENCIL_BIT;
    case IMAGE_ASPECT::DEPTH_STENCIL:
    default:
        return VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
    }
}

VkAccessFlags Convert::convert(const ACCESS &access)
{
    switch (access)
    {
    case ACCESS::NONE:
        return VK_ACCESS_NONE;
    case ACCESS::MEMORY_READ:
        return VK_ACCESS_MEMORY_READ_BIT;
    case ACCESS::MEMORY_WRITE:
        return VK_ACCESS_MEMORY_WRITE_BIT;
    case ACCESS::SHADER_READ:
        return VK_ACCESS_SHADER_READ_BIT;
    case ACCESS::TRANSFER_WRITE:
        return VK_ACCESS_TRANSFER_WRITE_BIT;
    case ACCESS::COLOR_ATTACHMENT_READ:
        return VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
    case ACCESS::COLOR_ATTACHMENT_READ_WRITE:
        return VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    case ACCESS::COLOR_ATTACHMENT_WRITE:
        return VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    case ACCESS::DEPTH_STENCIL_ATTACHMENT_READ:
        return VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
    case ACCESS::DEPTH_STENCIL_ATTACHMENT_READ_WRITE:
        return VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
    case ACCESS::DEPTH_STENCIL_ATTACHMENT_WRITE:
        return VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
    case ACCESS::INDIRECT_COMMAND_READ:
        return VK_ACCESS_INDIRECT_COMMAND_READ_BIT;
    case ACCESS::INPUT_ATTACHMENT_READ:
        return VK_ACCESS_INPUT_ATTACHMENT_READ_BIT;
    case ACCESS::SHADER_WRITE_BIT:
        return VK_ACCESS_SHADER_WRITE_BIT;
    case ACCESS::UNIFORM_READ:
        return VK_ACCESS_UNIFORM_READ_BIT;
    case ACCESS::VERTEX_ATTRIBUTE_READ:
    default:
        return VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;
    }
}

VkPipelineStageFlags Convert::convert(const PIPELINE_STAGE &stage)
{
    switch (stage)
    {
    case PIPELINE_STAGE::NONE:
        return VK_PIPELINE_STAGE_NONE;
    case PIPELINE_STAGE::FRAGMENT_SHADER:
        return VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    case PIPELINE_STAGE::GEOMETRY_SHADER:
        return VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT;
    case PIPELINE_STAGE::TOP_OF_PIPE:
        return VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    case PIPELINE_STAGE::TRANSFER:
        return VK_PIPELINE_STAGE_TRANSFER_BIT;
    case PIPELINE_STAGE::VERTEX_INPUT:
        return VK_PIPELINE_STAGE_VERTEX_INPUT_BIT;
    case PIPELINE_STAGE::VERTEX_SHADER:
        return VK_PIPELINE_STAGE_VERTEX_SHADER_BIT;
    case PIPELINE_STAGE::ALL_COMMANDS:
        return VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
    case PIPELINE_STAGE::ALL_GRAPHICS:
        return VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT;
    case PIPELINE_STAGE::BOTTOM_OF_PIPE:
        return VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
    case PIPELINE_STAGE::COLOR_ATTACHMENT_OUTPUT:
        return VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    case PIPELINE_STAGE::COMPUTE_SHADER:
        return VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
    case PIPELINE_STAGE::DRAW_INDIRECT:
        return VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT;
    case PIPELINE_STAGE::EARLY_FRAGMENT_TESTS:
        return VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    case PIPELINE_STAGE::LATE_FRAGMENT_TESTS:
        return VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
    case PIPELINE_STAGE::TESSELLATION_CONTROL_SHADER:
        return VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT;
    case PIPELINE_STAGE::TESSELLATION_EVALUATION_SHADER:
    default:
        return VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT;
    }
}

VkIndexType Convert::convert(const INDEX_TYPE &type)
{
    switch (type)
    {
    case INDEX_TYPE::UINT8:
        return VK_INDEX_TYPE_UINT8;
    case INDEX_TYPE::UINT16:
        return VK_INDEX_TYPE_UINT16;
    case INDEX_TYPE::UINT32:
    default:
        return VK_INDEX_TYPE_UINT32;
    }
}

VkAttachmentLoadOp Convert::convert(const LOAD_OP &op)
{
    switch (op)
    {
    case LOAD_OP::LOAD_OP_CLEAR:
        return VK_ATTACHMENT_LOAD_OP_CLEAR;
    case LOAD_OP::LOAD_OP_LOAD:
        return VK_ATTACHMENT_LOAD_OP_LOAD;
    case LOAD_OP::LOAD_OP_DONT_CARE:
    default:
        return VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    }
}

VkAttachmentStoreOp Convert::convert(const STORE_OP &op)
{
    return op == STORE_OP::STORE_OP_DONT_CARE ? VK_ATTACHMENT_STORE_OP_DONT_CARE : VK_ATTACHMENT_STORE_OP_STORE;
}

VkSampleCountFlagBits Convert::convert(const SAMPLES &samples)
{
    switch (samples)
    {
    case SAMPLES::_2BIT:
        return VK_SAMPLE_COUNT_2_BIT;
    case SAMPLES::_4BIT:
        return VK_SAMPLE_COUNT_4_BIT;
    case SAMPLES::_8BIT:
        return VK_SAMPLE_COUNT_8_BIT;
    case SAMPLES::_16BIT:
        return VK_SAMPLE_COUNT_16_BIT;
    case SAMPLES::_32BIT:
        return VK_SAMPLE_COUNT_32_BIT;
    case SAMPLES::_64BIT:
        return VK_SAMPLE_COUNT_64_BIT;
    case SAMPLES::_1BIT:
    default:
        return VK_SAMPLE_COUNT_1_BIT;
    }
}

VkPipelineBindPoint Convert::convert(const PIPELINE_BIND_POINT &bind_point)
{
    return bind_point == PIPELINE_BIND_POINT::COMPUTER ? VK_PIPELINE_BIND_POINT_COMPUTE : VK_PIPELINE_BIND_POINT_GRAPHICS;
}

VkImageUsageFlags Convert::convert(const IMAGE_USAGE &usage)
{
    switch (usage)
    {
    case IMAGE_USAGE::SAMPLED:
        return VK_IMAGE_USAGE_SAMPLED_BIT;
    case IMAGE_USAGE::TRANSFER_DST:
        return VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    case IMAGE_USAGE::TRANSFER_SRC:
        return VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    case IMAGE_USAGE::SAMPLED_TRANSFER_DST:
        return VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    case IMAGE_USAGE::DEPTH_STENCIL_ATTACHMENT:
        return VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    case IMAGE_USAGE::SAMPLED_TRANSFER_SRC:
    default:
        return VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    }
}

VkDescriptorType Convert::convert(const DESCRIPTOR_TYPE &type)
{
    switch (type)
    {
        case DESCRIPTOR_TYPE::UNIFORM_BUFFER:
            return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        case DESCRIPTOR_TYPE::UNIFORM_BUFFER_DYNAMIC:
            return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
        case DESCRIPTOR_TYPE::COMBINED_IMAGE_SAMPLER:
        default:
            return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    }
}

} // namespace core::vulkan
#endif //defined(CORE_INCLUDE_VULKAN)

int core::opengl::Convert::convert(const TYPE &type)
{
    switch (type)
    {
    case TYPE::INT:
        return GL_INT;
    case TYPE::UNSIGNED_INT:
        return GL_UNSIGNED_INT;
    case TYPE::FLOAT:
        return GL_FLOAT;
    case TYPE::DOUBLE:
    default:
        return GL_DOUBLE;
    }
}

unsigned int core::opengl::Convert::convertSizeType(const TYPE &type)
{
    switch (type)
    {
    case TYPE::INT:
        return sizeof(GLint);
    case TYPE::UNSIGNED_INT:
        return sizeof(GLuint);
    case TYPE::FLOAT:
        return sizeof(GLfloat);
    case TYPE::DOUBLE:
    default:
        return sizeof(GLdouble);
    }
}

int core::opengl::Convert::convertAndAlignment(const IMAGE_INTERNAL_FORMAT &format)
{
    switch (format)
    {
    case IMAGE_INTERNAL_FORMAT::R8:
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        return GL_R8;
    case IMAGE_INTERNAL_FORMAT::R16:
        glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
        return GL_R16;
    case IMAGE_INTERNAL_FORMAT::R32F:
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        return GL_R32F;
    case IMAGE_INTERNAL_FORMAT::R16F:
        glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
        return GL_R16F;
    case IMAGE_INTERNAL_FORMAT::RG8:
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        return GL_RG8;
    case IMAGE_INTERNAL_FORMAT::RG16:
        glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
        return GL_RG16;
    case IMAGE_INTERNAL_FORMAT::RG16F:
        glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
        return GL_RG16F;
    case IMAGE_INTERNAL_FORMAT::RG32F:
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        return GL_RG32F;
    case IMAGE_INTERNAL_FORMAT::RGB16:
        glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
        return GL_RGB16;
    case IMAGE_INTERNAL_FORMAT::RGBA16:
        glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
        return GL_RGBA16;
    case IMAGE_INTERNAL_FORMAT::RGB16F:
        glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
        return GL_RGB16F;
    case IMAGE_INTERNAL_FORMAT::RGB32F:
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        return GL_RGB32F;
    case IMAGE_INTERNAL_FORMAT::RGBA16F:
        glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
        return GL_RGBA16F;
    case IMAGE_INTERNAL_FORMAT::RGBA32F:
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        return GL_RGBA32F;
    case IMAGE_INTERNAL_FORMAT::RGB8:
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        return GL_RGB8;
    case IMAGE_INTERNAL_FORMAT::DEPTH24_STENCIL8:
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        return GL_DEPTH24_STENCIL8;
    case IMAGE_INTERNAL_FORMAT::DEPTH32F_STENCIL8:
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        return GL_DEPTH32F_STENCIL8;
    case IMAGE_INTERNAL_FORMAT::DEPTH_COMPONENT16:
        glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
        return GL_DEPTH_COMPONENT16;
    case IMAGE_INTERNAL_FORMAT::DEPTH_COMPONENT24:
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        return GL_DEPTH_COMPONENT24;
    case IMAGE_INTERNAL_FORMAT::RGBA8:
    default:
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        return GL_RGBA8;
    }
}

unsigned int core::opengl::Convert::convert(const IMAGE_FORMAT &format)
{
    switch (format)
    {
    case IMAGE_FORMAT::ALPHA:
        return GL_ALPHA;
    case IMAGE_FORMAT::BGR:
        return GL_BGR;
    case IMAGE_FORMAT::RGB:
        return GL_RGB;
    case IMAGE_FORMAT::BGRA:
        return GL_BGRA;
    case IMAGE_FORMAT::BLUE:
        return GL_BLUE;
    case IMAGE_FORMAT::DEPTH_COMPONENT:
        return GL_DEPTH_COMPONENT;
    case IMAGE_FORMAT::DEPTH_STENCIL:
        return GL_DEPTH_STENCIL;
    case IMAGE_FORMAT::GREEN:
        return GL_GREEN;
    case IMAGE_FORMAT::RED:
        return GL_RED;
    case IMAGE_FORMAT::RG:
        return GL_RG;
    case IMAGE_FORMAT::RGBA:
    default:
        return GL_RGBA;
    }
}


