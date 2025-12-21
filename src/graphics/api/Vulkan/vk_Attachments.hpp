//
// Created by kisly on 31.10.2025.
//

#ifndef VK_ATTACHMENTS_HPP
#define VK_ATTACHMENTS_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)
#include "../../../types/apiTypes.hpp"

namespace core::vulkan
{
	enum class LOAD_OP : int
	{
		LOAD_OP_CLEAR,
		LOAD_OP_LOAD
	};

	struct AttachmentsInfo
	{
		LOAD_OP loadOp = LOAD_OP::LOAD_OP_CLEAR;
		IMAGE_LAYOUT initLayout = IMAGE_LAYOUT::UNDEFINED;
		IMAGE_LAYOUT finalLayout = IMAGE_LAYOUT::PRESENT_SRC_KHR;
	};
}

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_ATTACHMENTS_HPP
