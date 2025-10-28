//
// Created by kisly on 23.09.2025.
//

#ifndef GL_DESCRIPTORCONTAINER_HPP
#define GL_DESCRIPTORCONTAINER_HPP

namespace core::opengl
{
	class DescriptorContainer
	{
	protected:
		unsigned int id = 0;
	};

	class FunctionBindContainer : public DescriptorContainer
	{
	public:
		virtual void bind() const = 0;
		virtual void unBind() const = 0;
	};

	class FunctionUseContainer : public DescriptorContainer
	{
	public:
		virtual void use() const = 0;
		virtual void unUse() const = 0;
	};
}

#endif //GL_DESCRIPTORCONTAINER_HPP
