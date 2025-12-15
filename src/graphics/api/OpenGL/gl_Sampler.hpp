//
// Created by kisly on 15.12.2025.
//

#ifndef GL_SAMPLER_HPP
#define GL_SAMPLER_HPP

#include "../../../types/apiTypes.hpp"

namespace core::opengl
{
    struct SamplerCreateInfo
    {
        TEXTURE_WRAP TEXTURE_WRAP_S = TEXTURE_WRAP::MIRRORED_REPEAT;
        TEXTURE_WRAP TEXTURE_WRAP_T = TEXTURE_WRAP::MIRRORED_REPEAT;
        TEXTURE_FILTER MIN_FILTER = TEXTURE_FILTER::LINEAR;
        TEXTURE_FILTER MAG_FILTER = TEXTURE_FILTER::LINEAR;
    };

    class Sampler
    {
    private:
        unsigned int id = 0;

        Sampler(const SamplerCreateInfo& createInfo);

    public:
        ~Sampler();

        static Sampler create(const SamplerCreateInfo& info);
        static Sampler* ptrCreate(const SamplerCreateInfo& info);

        void bind(unsigned int unit = 0) const;
        void unBind() const;
    };
} // core::opengl

#endif // GL_SAMPLER_HPP
