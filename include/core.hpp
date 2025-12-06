//
// Created by kisly on 13.07.2025.
//

#ifndef CORE_HPP_
#define CORE_HPP_

#include "../src/util/coders.hpp"
#include "../src/util/console.hpp"
#include "../src/util/vector.hpp"
#include "../src/util/time.hpp"
#include "../src/window/Window.hpp"
#include "../src/window/Event.hpp"
#include "../src/window/Cursor.hpp"
#include "../src/window/Monitor.hpp"
#include "../src/graphics/commons/Camera.hpp"
#include "../src/graphics/api/OpenGL/gl_vertexBuffer.hpp"
#include "../src/graphics/api/OpenGL/gl_shaderProgram.hpp"
#include "../src/graphics/api/OpenGL/gl_commands.hpp"
#include "../src/graphics/api/OpenGL/gl_texture.hpp"
#include "../src/graphics/api/OpenGL/gl_elementBuffers.hpp"
#include "../src/graphics/api/OpenGL/gl_FrameBuffer.hpp"
#include "../src/graphics/api/Vulkan/vk_Instance.hpp"
#include "../src/graphics/api/Vulkan/vk_Surface.hpp"
#include "../src/graphics/api/Vulkan/vk_PhysicalDevices.hpp"
#include "../src/graphics/api/Vulkan/vk_Device.hpp"
#include "../src/graphics/api/Vulkan/vk_SwapChain.hpp"
#include "../src/graphics/api/Vulkan/vk_Attachments.hpp"
#include "../src/graphics/api/Vulkan/vk_RenderPass.hpp"
#include "../src/graphics/api/Vulkan/vk_FrameBuffer.hpp"
#include "../src/graphics/api/Vulkan/vk_CommandPool.hpp"
#include "../src/graphics/api/Vulkan/vk_CommandBuffer.hpp"
#include "../src/graphics/api/Vulkan/vk_Semaphore.hpp"
#include "../src/graphics/api/Vulkan/vk_Queue.hpp"
#include "../src/graphics/api/Vulkan/vk_Pipeline.hpp"
#include "../src/graphics/api/Vulkan/vk_ShaderStage.hpp"
#include "../src/graphics/api/Vulkan/vk_VertexBuffer.hpp"
#include "../src/graphics/api/Vulkan/vk_ElementBuffer.hpp"
#include "../src/graphics/api/Vulkan/vk_Buffer.hpp"
#include "../src/graphics/api/Vulkan/vk_Descriptor.hpp"
#include "../src/graphics/api/Vulkan/vk_Image.hpp"
#include "../src/file/image.hpp"
#include "../src/file/code.hpp"
#include "../src/file/wav.hpp"
#include "../src/file/models/m_types.hpp"
#include "../src/file/models/m_OBJ.hpp"
#include "../src/file/animation/a_FBX.hpp"
#include "../src/math/math.hpp"
#include "../src/math/Vectors.hpp"
#include "../src/math/Matrix4.hpp"
#include "../src/math/Quaternion.hpp"
#include "../src/audio/aDevice.hpp"
#include "../src/audio/aBuffer.hpp"
#include "../src/audio/aSource.hpp"
#include "../src/types/size.hpp"
#include "../src/types/color.hpp"
#include "../src/types/pos.hpp"
#include "../src/types/apiTypes.hpp"
#include "../src/types/key.hpp"
#include "../src/file/script/lua_Runner.hpp"
#include "../src/file/script/lua_Stack.hpp"
#include "../src/file/script/lua_Table.hpp"
#include "../src/file/script/lua_Function.hpp"

namespace core::Core
{
    /// @brief функция для инициализации библиотеки
    void Init();

    /// @brief функция для уничтожения данных библиотеки
    void Terminate();

    /// @brief возвращает время с момента инициализации библиотеки
    /// @return милисекунды
    [[nodiscard]] double getTime();
}

#endif // CORE_HPP_
