
cmake_minimum_required(VERSION 3.5)
project(CoreGL)
set(CMAKE_CXX_STANDARD 20)

set(CoreGL_source
        src/core.cpp
        src/util/coders.cpp
        src/util/console.cpp
        src/util/vector.cpp
        src/util/time.cpp
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
        src/graphics/api/Vulkan/vk_Instance.cpp
        src/graphics/api/Vulkan/vk_Surface.cpp
        src/graphics/api/Vulkan/vk_PhysicalDevices.cpp
        src/graphics/api/Vulkan/vk_Device.cpp
        src/graphics/api/Vulkan/vk_SwapChain.cpp
        src/graphics/api/Vulkan/vk_RenderPass.cpp
        src/graphics/api/Vulkan/vk_FrameBuffer.cpp
        src/graphics/api/Vulkan/vk_CommandPool.cpp
        src/graphics/api/Vulkan/vk_CommandBuffer.cpp
        src/graphics/api/Vulkan/vk_Semaphore.cpp
        src/graphics/api/Vulkan/vk_Queue.cpp
        src/graphics/api/Vulkan/vk_Pipeline.cpp
        src/graphics/api/Vulkan/vk_ShaderStage.cpp
        src/graphics/api/Vulkan/vk_VertexBuffer.cpp
        src/graphics/api/Vulkan/vk_ElementBuffer.cpp
        src/graphics/api/Vulkan/vk_Buffer.cpp
        src/graphics/api/Vulkan/vk_Descriptor.cpp
        src/graphics/api/Vulkan/vk_Image.cpp
        src/file/code.cpp
        src/file/image.cpp
        src/file/wav.cpp
        src/file/models/m_OBJ.cpp
        src/file/animation/a_FBX.cpp
        src/math/math.cpp
        src/math/Matrix4.cpp
        src/math/Quaternion.cpp
        src/math/Vector2.cpp
        src/math/Vector3.cpp
        src/math/Vector4.cpp
        src/audio/aDevice.cpp
        src/audio/aBuffer.cpp
        src/audio/aSource.cpp
        src/types/color.cpp
        src/types/pos.hpp
        src/types/apiTypes.hpp
        src/types/key.hpp
        src/types/apiTypes.cpp
        src/file/script/lua_Runner.cpp
        src/file/script/lua_Stack.cpp
        src/file/script/lua_Table.cpp
        src/file/script/lua_Function.cpp
        src/file/script/lua_Array.cpp
)

add_library(CoreGL STATIC ${CoreGL_source})

# link GLFW
set(BUILD_SHARED_LIBS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
set(GLFW_VULKAN_STATIC ON)

add_subdirectory(package/glfw)
target_link_libraries(${PROJECT_NAME} glfw)
target_include_directories(${PROJECT_NAME} PRIVATE package/glfw/include)

# link glew
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "Build shared libraries")
set(BUILD_UTILS OFF CACHE INTERNAL "Build utilities")
add_subdirectory(package/glew-2.1.0/build/cmake)
target_link_libraries(${PROJECT_NAME} glew_s)
target_include_directories(${PROJECT_NAME} PRIVATE package/glew-2.1.0/include)

# link stb_image
target_include_directories(${PROJECT_NAME} PRIVATE package/stb)

# link openAL
set(LIBTYPE STATIC)
add_subdirectory(package/openal-soft)
target_link_libraries(${PROJECT_NAME} OpenAL)
target_include_directories(${PROJECT_NAME} PRIVATE package/openal-soft/include)

# link vulkan
set(VULKAN_SDK $ENV{VULKAN_SDK} CACHE PATH "Path to the Vulkan SDK")
message(STATUS "VULKAN_SDK: ${VULKAN_SDK}")
find_package(Vulkan REQUIRED)
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)
target_include_directories(${PROJECT_NAME} PRIVATE ${Vulkan_INCLUDE_DIRS})

# link assimp
set(BUILD_SHARED_LIBS OFF)
set(ASSIMP_BUILD_ZLIB ON)
set(DASSIMP_BUILD_ZLIB ON)
add_subdirectory(package/assimp)
target_link_libraries(${PROJECT_NAME} assimp)
target_include_directories(${PROJECT_NAME} PRIVATE package/assimp/include)

# link nlohmann-json
target_include_directories(${PROJECT_NAME} PRIVATE package/nlohmann)

# link lua-5.4.8
add_subdirectory(package/lua-5.4.8)
target_link_libraries(${PROJECT_NAME} lua)
target_include_directories(${PROJECT_NAME} PRIVATE package/lua-5.4.8/src)

