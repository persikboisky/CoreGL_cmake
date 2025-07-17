//
// Created by kisly on 17.07.2025.
//

#include "aBuffer.hpp"
#include "../file/wav.hpp"
#include "../util/coders.hpp"
#include <al.h>
#include <iostream>

static unsigned int createBuffer(
    const short& channels,
    const short& bitsPerSample,
    const std::vector<char>& data,
    const int sampleRate
)
{
    unsigned int id;
    alGenBuffers(1, &id);
    if (id <= 0)
    {
        throw core::coders(32);
    }

    ALenum format = AL_FORMAT_MONO8;
    if (channels == 1 && bitsPerSample == 8)
        format = AL_FORMAT_MONO8;
    else if (channels == 1 && bitsPerSample == 16)
        format = AL_FORMAT_MONO16;
    else if (channels == 2 && bitsPerSample == 8)
        format = AL_FORMAT_STEREO8;
    else if (channels == 2 && bitsPerSample == 16)
        format = AL_FORMAT_STEREO16;

    std::cout << channels << std::endl;
    std::cout << data.size() << std::endl;
    std::cout << sampleRate << std::endl;
    alBufferData(id, format, data.data(), data.size(), sampleRate);

    return id;
}

namespace core
{
    audio::Buffer::Buffer(const char *path)
    {
        wav* song = wav::ptrLoad(path);

        this->id = createBuffer(
            song->getChannels(),
            song->getBitsPerSample(),
            song->getData(),
            song->getSampleRate()
        );

        delete song;
    }

    audio::Buffer::Buffer(wav &obj)
    {
        this->id = createBuffer(
            obj.getChannels(),
            obj.getBitsPerSample(),
            obj.getData(),
            obj.getSampleRate()
        );
    }

    audio::Buffer::~Buffer()
    {
        alDeleteBuffers(1, &this->id);
    }

    audio::Buffer audio::Buffer::create(const char *path)
    {
        return audio::Buffer(path);
    }

    audio::Buffer audio::Buffer::create(wav &obj)
    {
        return audio::Buffer(obj);
    }

    audio::Buffer *audio::Buffer::ptrCreate(const char *path)
    {
        return new audio::Buffer(path);
    }

    audio::Buffer *audio::Buffer::ptrCreate(wav &obj)
    {
        return new audio::Buffer(obj);
    }

    unsigned int audio::Buffer::getID()
    {
        return this->id;
    }

} // core

