
target_sources(${PROJECT_NAME} PRIVATE
        src/core.cpp
        src/util/coders.cpp
        src/util/console.cpp
        src/util/types.cpp
        src/util/vector.cpp
        src/util/time.cpp
        src/window/Window.cpp
        src/window/Event.cpp
        src/window/Cursor.cpp
        src/window/Monitor.cpp
        src/graphics/commons/fbo.cpp
        src/graphics/commons/shader.cpp
        src/graphics/commons/Camera.cpp
        src/graphics/commons/vao.cpp
        src/graphics/commons/ebo.cpp
        src/graphics/commons/texture.cpp
        src/graphics/commons/gl.cpp
        src/graphics/renderer/gResource.cpp
        src/graphics/renderer/Rect.cpp
        src/graphics/vulkan/vInstance.cpp
        src/graphics/vulkan/vResource.cpp
        src/graphics/vulkan/vDevices.cpp
        src/file/code.cpp
        src/file/mtl.cpp
        src/file/obj.cpp
        src/file/image.cpp
        src/file/wav.cpp
        src/math/math.cpp
        src/math/Vector2.cpp
        src/math/Vector3.cpp
        src/math/Vector4.cpp
        src/math/Matrix4.cpp
        src/audio/aDevice.cpp
        src/audio/aBuffer.cpp
        src/audio/aSource.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE include)

# link GLFW
set(BUILD_SHARED_LIBS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
set(GLFW_VULKAN_STATIC ON)

add_subdirectory(package/glfw)
target_link_libraries(${PROJECT_NAME} glfw)
target_include_directories(${PROJECT_NAME} PRIVATE package/glfw/include)

# link glad
add_library(glad STATIC package/glad/include/glad/glad.h package/glad/src/glad.c)
target_link_libraries(${PROJECT_NAME} glad)
target_include_directories(${PROJECT_NAME} PRIVATE package/glad/include)

# link stb_image
target_include_directories(${PROJECT_NAME} PRIVATE package/stb)

# link openAL
set(LIBTYPE STATIC)
add_subdirectory(package/openal-soft-1.22.2)
target_link_libraries(${PROJECT_NAME} OpenAL)
target_include_directories(${PROJECT_NAME} PRIVATE package/openal-soft-1.22.2/include)

# link vulkan
find_package(Vulkan REQUIRED)
target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${Vulkan_INCLUDE_DIRS})
