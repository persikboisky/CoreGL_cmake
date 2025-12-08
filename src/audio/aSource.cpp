//
// Created by kisly on 17.07.2025.
//

#include "aSource.hpp"
#include "Abuffer.hpp"
#include "../types/pos.hpp"
#include "../util/coders.hpp"
#include "../math/Vectors.hpp"
#include <AL/al.h>

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

    void audio::Source::setMaxVolume(float value) const
    {
        alSourcef(this->id, AL_MAX_GAIN, value);
    }

    void audio::Source::setMinVolume(float value) const
    {
        alSourcef(this->id, AL_MIN_GAIN, value);
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
        return state == AL_PLAYING;
    }

    void audio::Source::setPos(float x, float y, float z) const
    {
        alSource3f(this->id, AL_POSITION, x, y, z);
    }

    void audio::Source::setPos(const Pos3f& pos) const
    {
        alSource3f(this->id, AL_POSITION, pos.x, pos.y, pos.z);
    }


    void audio::Source::setPos(const math::Vec3& pos) const
    {
        alSource3f(this->id, AL_POSITION, pos.x, pos.y, pos.z);
    }

    void audio::Source::setVel(float x, float y, float z) const
    {
        alSource3f(this->id, AL_VELOCITY, x, y, z);
    }

    void audio::Source::setVel(const math::Vec3& vel) const
    {
        alSource3f(this->id, AL_VELOCITY, vel.x, vel.y, vel.z);
    }

    void audio::Source::setDirect(float x, float y, float z) const
    {
        alSource3f(this->id, AL_DIRECTION, x, y, z);
    }

    void audio::Source::setDirect(const math::Vec3& direct) const
    {
        alSource3f(this->id, AL_DIRECTION, direct.x, direct.y, direct.z);
    }

	void audio::Source::setFov(float agree) const
	{
        alSourcef(this->id, AL_CONE_INNER_ANGLE, agree);
	}

    void audio::Source::setReferenceDistance(float distance)
    {
        alSourcef(this->id, AL_REFERENCE_DISTANCE, distance);
    }
}

