//
// Created by kisly on 13.07.2025.
//

#ifndef CORE_HPP_
#define CORE_HPP_

#include "../../src/graphics/api/OpenGL/gl_FrameBuffer.hpp"
#include "../../src/graphics/api/OpenGL/gl_Sampler.hpp"
#include "../../src/graphics/api/OpenGL/gl_commands.hpp"
#include "../../src/graphics/api/OpenGL/gl_elementBuffers.hpp"
#include "../../src/graphics/api/OpenGL/gl_shaderProgram.hpp"
#include "../../src/graphics/api/OpenGL/gl_texture.hpp"
#include "../../src/graphics/api/OpenGL/gl_vertexBuffer.hpp"
#include "../../src/graphics/commons/Camera.hpp"
#include "../../src/loaders/Code.hpp"
#include "../../src/loaders/image.hpp"
#include "../../src/loaders/animation/a_FBX.hpp"
#include "../../src/loaders/models/m_FBX.hpp"
#include "../../src/loaders/models/m_OBJ.hpp"
#include "../../src/loaders/models/m_types.hpp"
#include "../../src/loaders/script/lua_Array.hpp"
#include "../../src/loaders/script/lua_Function.hpp"
#include "../../src/loaders/script/lua_Runner.hpp"
#include "../../src/loaders/script/lua_Stack.hpp"
#include "../../src/loaders/script/lua_Table.hpp"
#include "../../src/loaders/ttf.hpp"
#include "../../src/loaders/wav.hpp"
#include "../../src/math/Matrix4.hpp"
#include "../../src/math/Quaternion.hpp"
#include "../../src/math/Vectors.hpp"
#include "../../src/math/math.hpp"
#include "../../src/types/apiTypes.hpp"
#include "../../src/types/color.hpp"
#include "../../src/types/key.hpp"
#include "../../src/types/pos.hpp"
#include "../../src/types/size.hpp"
#include "../../src/util/Coders.hpp"
#include "../../src/util/console.hpp"
#include "../../src/util/time.hpp"
#include "../../src/util/vector.hpp"
#include "../../src/window/Cursor.hpp"
#include "../../src/window/Event.hpp"
#include "../../src/window/Monitor.hpp"
#include "../../src/window/Window.hpp"

namespace core::Core
{
    /// @brief функция для инициализации библиотеки
    void Init();

    /// @brief функция для уничтожения данных библиотеки
    void Terminate();

    /// @brief возвращает время с момента инициализации библиотеки
    /// @return мили-секунды
    [[nodiscard]] double getTime();
}

#endif // CORE_HPP_
