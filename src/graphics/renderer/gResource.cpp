//
// Created by kisly on 23.07.2025.
//

#include "gResource.hpp"
#include "../commons/shader.hpp"
#include <string>

unsigned int core::gResource::rectIdShader = 0;

namespace core
{

    const std::string listsShadersCode[2] = {
            "#version 330 core\n"
            "layout (location=0) in vec2 aPos;\n"
            "layout (location=1) in vec2 aTextureCoord;\n"
            "uniform mat4 model = mat4(1.0);\n"
            "out vec2 vTextureCoord;\n"
            "void main(){\n"
            "vTextureCoord = aTextureCoord;\n"
            "gl_Position = model * vec4(aPos, 0.0, 1.0);\n"
            "}",
            "#version 330 core\n"
            "out vec4 fColor;\n"
            "in vec2 vTextureCoord;\n"
            "uniform vec4 uColor = vec4(1.0);\n"
            "uniform sampler2D text;\n"
            "void main(){\n"
            "fColor = uColor * texture(text, vTextureCoord);\n"
            "}"
    };

    unsigned int gResource::loadShader(unsigned int number)
    {
        return shader::createProgramFromCode(
                listsShadersCode[number * 2].c_str(),
                listsShadersCode[number * 2 + 1].c_str()
        );
    }
} // core

