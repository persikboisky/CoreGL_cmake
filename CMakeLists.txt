
cmake_minimum_required(VERSION 3.5)
project(CoreGL)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 23)

set(CoreGL_source
        src/core.cpp
        src/util/coders.cpp
        src/util/console.cpp
        src/util/vector.cpp
        src/util/time.cpp
        src/util/coders.hpp
        src/window/Window.cpp
        src/window/Event.cpp
        src/window/Cursor.cpp
        src/window/Monitor.cpp
        src/graphics/commons/Camera.cpp
        src/graphics/api/OpenGL/gl_vertexBuffer.cpp
        src/graphics/api/OpenGL/gl_shaderProgram.cpp
        src/graphics/api/OpenGL/gl_commands.cpp
        src/graphics/api/OpenGL/gl_texture.cpp
        src/graphics/api/OpenGL/gl_elementBuffers.cpp
        src/graphics/api/OpenGL/gl_FrameBuffer.cpp
        src/graphics/api/OpenGL/gl_Sampler.cpp
        src/math/math.cpp
        src/math/Matrix4.cpp
        src/math/Quaternion.cpp
        src/math/Vector2.cpp
        src/math/Vector3.cpp
        src/math/Vector4.cpp
        src/types/color.cpp
        src/types/apiTypes.cpp
        src/loaders/script/lua_Runner.cpp
        src/loaders/script/lua_Stack.cpp
        src/loaders/script/lua_Table.cpp
        src/loaders/script/lua_Function.cpp
        src/loaders/script/lua_Array.cpp
        src/loaders/models/m_FBX.cpp
        src/loaders/models/m_OBJ.cpp
        src/loaders/animation/a_FBX.cpp
        src/loaders/ttf.cpp
        src/loaders/code.cpp
        src/loaders/image.cpp
        src/loaders/wav.cpp
)

set(CoreGL_vulkan
        src/graphics/api/Vulkan/vk_VertexBuffer.cpp
        src/graphics/api/Vulkan/vk_IndexBuffer.cpp
        src/graphics/api/Vulkan/core/vk_Instance.cpp
        src/graphics/api/Vulkan/core/vk_Surface.cpp
        src/graphics/api/Vulkan/core/vk_PhysicalDevices.cpp
        src/graphics/api/Vulkan/core/vk_Device.cpp
        src/graphics/api/Vulkan/core/vk_SwapChain.cpp
        src/graphics/api/Vulkan/core/vk_RenderPass.cpp
        src/graphics/api/Vulkan/core/vk_FrameBuffer.cpp
        src/graphics/api/Vulkan/core/vk_CommandPool.cpp
        src/graphics/api/Vulkan/core/vk_CommandBuffer.cpp
        src/graphics/api/Vulkan/core/vk_Sync.cpp
        src/graphics/api/Vulkan/core/vk_Queue.cpp
        src/graphics/api/Vulkan/core/vk_Pipeline.cpp
        src/graphics/api/Vulkan/core/vk_ShaderStage.cpp
        src/graphics/api/Vulkan/core/vk_Buffer.cpp
        src/graphics/api/Vulkan/core/vk_Descriptor.cpp
        src/graphics/api/Vulkan/core/vk_Image.cpp
)

set(CoreGL_audio
        src/audio/aDevice.cpp
        src/audio/aBuffer.cpp
        src/audio/aSource.cpp
        src/audio/aListener.cpp
)

add_library(CoreGL STATIC ${CoreGL_source} ${CoreGL_audio} ${CoreGL_vulkan})

# link GLFW
set(BUILD_SHARED_LIBS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
set(GLFW_VULKAN_STATIC ON)

add_subdirectory(package/glfw)
target_link_libraries(CoreGL glfw)
target_include_directories(CoreGL PRIVATE package/glfw/include)

# link glew
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "Build shared libraries")
set(BUILD_UTILS OFF CACHE INTERNAL "Build utilities")
add_subdirectory(package/glew-2.3.0/build/cmake)
target_link_libraries(CoreGL glew_s)
target_include_directories(CoreGL PRIVATE package/glew-2.3.0/include)

# link stb_image
target_include_directories(CoreGL PRIVATE package/stb)

# link openAL
set(LIBTYPE STATIC)
add_subdirectory(package/openal-soft)
target_link_libraries(CoreGL OpenAL)
target_include_directories(CoreGL PRIVATE package/openal-soft/include)

# link vulkan
set(VULKAN_SDK $ENV{VULKAN_SDK} CACHE PATH "Path to the Vulkan SDK")
message(STATUS "VULKAN_SDK: ${VULKAN_SDK}")
find_package(Vulkan REQUIRED)
target_link_libraries(CoreGL Vulkan::Vulkan)
target_include_directories(CoreGL PRIVATE ${Vulkan_INCLUDE_DIRS})

# link assimp
set(BUILD_SHARED_LIBS OFF)
set(ASSIMP_BUILD_ZLIB ON)
set(DASSIMP_BUILD_ZLIB ON)
set(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(package/assimp)
target_link_libraries(CoreGL assimp)
target_include_directories(CoreGL PRIVATE package/assimp/include)

# link lua-5.4.8
add_subdirectory(package/lua-5.4.8)
target_link_libraries(${PROJECT_NAME} lua)
target_include_directories(${PROJECT_NAME} PRIVATE package/lua-5.4.8/src)

# link freetype
add_subdirectory(package/freetype)
target_link_libraries(CoreGL freetype)
target_include_directories(CoreGL PRIVATE package/freetype/include)

# link termcolor
target_include_directories(CoreGL PRIVATE package/termcolor)

# link tomlplusplus
target_include_directories(CoreGL PRIVATE package/tomlplusplus)
