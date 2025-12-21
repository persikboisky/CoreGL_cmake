//
// Created by kisly on 29.11.2025.
//

#include "apiTypes.hpp"
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

} // namespace core::vulkan
#endif //defined(CORE_INCLUDE_VULKAN)
