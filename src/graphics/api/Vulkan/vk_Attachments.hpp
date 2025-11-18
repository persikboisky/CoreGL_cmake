//
// Created by kisly on 31.10.2025.
//

#ifndef VK_ATTACHMENTS_HPP
#define VK_ATTACHMENTS_HPP

#include "../../../modules.hpp"
#if defined(CORE_INCLUDE_VULKAN)

namespace core::vulkan
{
	enum class LoadOp : int
	{
		LOAD_OP_CLEAR,
		LOAD_OP_LOAD
	};

	enum class InitialLayout : int
	{
		LAYOUT_UNDEFINED,
		LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
		LAYOUT_SHADER_READ_ONLY_OPTIMAL
	};

	enum class FinalLayout : int
	{
		LAYOUT_PRESENT_SRC_KHR,
		LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
	};

	struct AttachmentsInfo
	{
		LoadOp loadOp = LoadOp::LOAD_OP_CLEAR;
		InitialLayout initLayout = InitialLayout::LAYOUT_UNDEFINED;
		FinalLayout finalLayout = FinalLayout::LAYOUT_PRESENT_SRC_KHR;
	};
}

#endif //defined(CORE_INCLUDE_VULKAN)
#endif //VK_ATTACHMENTS_HPP
