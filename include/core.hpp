//
// Created by kisly on 13.07.2025.
//

#ifndef CORE_HPP_
#define CORE_HPP_

#include "../src/util/coders.hpp"
#include "../src/util/console.hpp"
#include "../src/util/types.hpp"
#include "../src/util/vector.hpp"
#include "../src/util/time.hpp"
#include "../src/window/Window.hpp"
#include "../src/window/Event.hpp"
#include "../src/window/Cursor.hpp"
#include "../src/window/Monitor.hpp"
#include "../src/graphics/commons/fbo.hpp"
#include "../src/graphics/commons/shader.hpp"
#include "../src/graphics/commons/vao.hpp"
#include "../src/graphics/commons/Camera.hpp"
#include "../src/graphics/commons/ebo.hpp"
#include "../src/graphics/commons/texture.hpp"
#include "../src/graphics/renderer/Rect.hpp"
#include "../src/graphics/api/Vulkan/vk_Instance.hpp"
#include "../src/graphics/api/Vulkan/vk_physicalDevices.hpp"
#include "../src/graphics/api/Vulkan/vk_surface.hpp"
#include "../src/graphics/api/Vulkan/vk_device.hpp"
#include "../src/graphics/api/Vulkan/vk_swapChain.hpp"
#include "../src/graphics/api/Vulkan/vk_shaderModule.hpp"
#include "../src/graphics/api/Vulkan/vk_pipeline.hpp"
#include "../src/graphics/api/Vulkan/vk_renderPass.hpp"
#include "../src/graphics/api/Vulkan/vk_imageView.hpp"
#include "../src/graphics/api/Vulkan/vk_frameBuffer.hpp"
#include "../src/graphics/api/Vulkan/vk_commandBuffer.hpp"
#include "../src/graphics/api/Vulkan/vk_image.hpp"
#include "../src/graphics/api/Vulkan/vk_semaphore.hpp"
#include "../src/graphics/api/Vulkan/vk_graphicsQueue.hpp"
#include "../src/graphics/api/Vulkan/vk_commandPool.hpp"
#include "../src/graphics/api/Vulkan/vk_vertexBuffer.hpp"
#include "../src/graphics/api/Vulkan/vk_depthImageView.hpp"
#include "../src/graphics/api/OpenGL/gl_vertexBuffer.hpp"
#include "../src/graphics/api/OpenGL/gl_shaderProgram.hpp"
#include "../src/graphics/api/OpenGL/gl_commands.hpp"
#include "../src/graphics/api/OpenGL/gl_texture.hpp"
#include "../src/graphics/api/OpenGL/gl_elementBuffers.hpp"
#include "../src/file/image.hpp"
#include "../src/file/code.hpp"
#include "../src/file/mtl.hpp"
#include "../src/file/obj.hpp"
#include "../src/file/wav.hpp"
#include "../src/file/ttf.hpp"
#include "../src/math/math.hpp"
#include "../src/math/Vectors.hpp"
#include "../src/math/Matrix4.hpp"
#include "../src/audio/aDevice.hpp"
#include "../src/audio/aBuffer.hpp"
#include "../src/audio/aSource.hpp"

namespace core
{
    namespace Core
    {
        void Init();
        void Terminate();
        [[nodiscard]] double getTime();
    }
}

#endif // CORE_HPP_
