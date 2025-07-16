
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
        src/file/code.cpp
        src/file/mtl.cpp
        src/file/image.cpp
        src/math/math.cpp
        src/math/Vector2.cpp
        src/math/Vector3.cpp
        src/math/Vector4.cpp
        src/math/Matrix4.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE include)

# link GLFW
set(BUILD_SHARED_LIBS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)

add_subdirectory(package/glfw)
target_link_libraries(${PROJECT_NAME} glfw)
target_include_directories(${PROJECT_NAME} PRIVATE package/glfw/include)

# link glad
add_library(glad STATIC package/glad/include/glad/glad.h package/glad/src/glad.c)
target_link_libraries(${PROJECT_NAME} glad)
target_include_directories(${PROJECT_NAME} PRIVATE package/glad/include)

# link stb_image
target_include_directories(${PROJECT_NAME} PRIVATE package/stb)


