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

	public:
		virtual void bind() const = 0;
		virtual void unBind() const = 0;
	};
}

#endif //GL_DESCRIPTORCONTAINER_HPP
