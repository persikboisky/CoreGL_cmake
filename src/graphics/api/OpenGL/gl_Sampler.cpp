//
// Created by kisly on 15.12.2025.
//

#include "gl_Sampler.hpp"

#include <GL/glew.h>
#include <io.h>

namespace core::opengl
{
    static int convertWrap(const TEXTURE_WRAP& wrap)
    {
        switch (wrap)
        {
        case TEXTURE_WRAP::MIRRORED_REPEAT:
            return GL_MIRRORED_REPEAT;
        case TEXTURE_WRAP::CLAMP_TO_EDGE:
            return GL_CLAMP_TO_EDGE;
        case TEXTURE_WRAP::CLAMP_TO_BORDER:
            return GL_CLAMP_TO_BORDER;
        case TEXTURE_WRAP::REPEAT:
        default:
            return GL_REPEAT;
        }
    }

    static int convertFilter(const TEXTURE_FILTER& filter)
    {
        switch (filter)
        {
        case TEXTURE_FILTER::NEAREST:
            return GL_NEAREST;
        case TEXTURE_FILTER::LINEAR:
            return GL_LINEAR;
        case TEXTURE_FILTER::NEAREST_MIPMAP_NEAREST:
            return GL_NEAREST_MIPMAP_NEAREST;
        case TEXTURE_FILTER::LINEAR_MIPMAP_NEAREST:
            return GL_LINEAR_MIPMAP_NEAREST;
        case TEXTURE_FILTER::NEAREST_MIPMAP_LINEAR:
            return GL_NEAREST_MIPMAP_LINEAR;
        case TEXTURE_FILTER::LINEAR_MIPMAP_LINEAR:
        default:
            return GL_LINEAR_MIPMAP_LINEAR;
        }
    }

    Sampler::Sampler(const SamplerCreateInfo &createInfo)
    {
        glGenSamplers(1, &id);

        glSamplerParameteri(id, GL_TEXTURE_WRAP_S, convertWrap(createInfo.TEXTURE_WRAP_S));
        glSamplerParameteri(id, GL_TEXTURE_WRAP_T, convertWrap(createInfo.TEXTURE_WRAP_T));
        glSamplerParameteri(id, GL_TEXTURE_WRAP_R, GL_REPEAT);

        glSamplerParameteri(id, GL_TEXTURE_MIN_FILTER, convertFilter(createInfo.MIN_FILTER));
        glSamplerParameteri(id, GL_TEXTURE_MAG_FILTER, convertFilter(createInfo.MAG_FILTER));
    }

    Sampler::~Sampler()
    {
        glDeleteSamplers(1, &id);
    }

    Sampler Sampler::create(const SamplerCreateInfo &info)
    {
        return Sampler(info);
    }

    Sampler *Sampler::ptrCreate(const SamplerCreateInfo &info)
    {
        return new Sampler(info);
    }

    void Sampler::bind(unsigned int unit) const
    {
        glBindSampler(unit, id);
    }

    void Sampler::unBind() const
    {
        glBindSampler(0, 0);
    }

} // namespace core::opengl
