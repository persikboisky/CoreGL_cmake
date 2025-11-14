//
// Created by kisly on 31.10.2025.
//

#ifndef VK_ATTACHMENTS_HPP
#define VK_ATTACHMENTS_HPP

namespace core::vulkan
{
	enum class FormatAttachment : int
	{
		COLOR,
		DEPTH,
		STENCIL
	};

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
		FormatAttachment format = FormatAttachment::COLOR;
		LoadOp loadOp = LoadOp::LOAD_OP_CLEAR;
		InitialLayout initLayout = InitialLayout::LAYOUT_UNDEFINED;
		FinalLayout finalLayout = FinalLayout::LAYOUT_PRESENT_SRC_KHR;
	};
}

#endif //VK_ATTACHMENTS_HPP
