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
#include "../src/graphics/commons/gl.hpp"
#include "../src/file/image.hpp"
#include "../src/file/code.hpp"
#include "../src/file/mtl.hpp"
#include "../src/file/obj.hpp"
#include "../src/file/wav.hpp"
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

#endif //CORE_HPP_
