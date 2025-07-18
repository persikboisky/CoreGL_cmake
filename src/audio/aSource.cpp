//
// Created by kisly on 17.07.2025.
//

#include "aSource.hpp"
#include "Abuffer.hpp"
#include "../util/types.hpp"
#include "../util/coders.hpp"
#include <AL/al.h>
#include <iostream>

namespace core
{
    audio::Source::Source() : id(0)
    {
        alGenSources(1, &this->id);
        if (this->id <= 0)
        {
            throw core::coders(33);
        }
    }

    audio::Source::~Source()
    {
        this->stop();
        alDeleteSources(1, &this->id);
    }

    audio::Source audio::Source::create()
    {
        return Source();
    }

    audio::Source* audio::Source::ptrCreate()
    {
        return new Source();
    }

    void audio::Source::linkBuffer(audio::Buffer buffer) const
    {
        alSourcei(this->id, AL_BUFFER, buffer.getID());
    }

    void audio::Source::setVolume(float value) const
    {
        alSourcef(this->id, AL_GAIN, value);
    }

    void audio::Source::setSpeed(float value) const
    {
        alSourcef(this->id, AL_PITCH, value);
    }

    void audio::Source::looping(bool flag) const
    {
        alSourcei(this->id, AL_LOOPING, flag);
    }

    void audio::Source::play() const
    {
        alSourcePlay(this->id);
    }

    void audio::Source::pause() const
    {
        alSourcePause(this->id);
    }

    void audio::Source::stop() const
    {
        alSourceStop(this->id);
        alSourceRewind(this->id);
    }

    void audio::Source::resume() const
    {
        this->play();
    }

    bool audio::Source::isPlaying() const
    {

        ALint state;
        alGetSourcei(this->id, AL_SOURCE_STATE, &state);
        return (state == AL_PLAYING);
    }

    void audio::Source::setPos(float x, float y, float z) const
    {
        alSource3f(this->id, AL_POSITION, x, y, z);
    }

    void audio::Source::setPos(pos3f pos) const
    {
        alSource3f(this->id, AL_POSITION, pos.x, pos.y, pos.z);
    }

    void audio::Source::setVelocity(float x, float y, float z) const
    {
        alSource3f(this->id, AL_VELOCITY, x, y, z);
    }
}

