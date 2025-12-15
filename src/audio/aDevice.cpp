//
// Created by kisly on 17.07.2025.
//

#include "aDevice.hpp"
#include "../config.hpp"
#include "../util/Coders.hpp"
#include "../util/console.hpp"
#include <AL/alc.h>
#include <AL\al.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <vector>

namespace core
{
    audio::Device::Device()
    {
        this->device = alcOpenDevice(nullptr);

        if (!this->device)
        {
            throw Coders(24);
        }

        this->DeviceName = alcGetString(NULL, ALC_DEVICE_SPECIFIER);

        if (CORE_INFO)
        {
            console::printTime();
            std::cout << "Ok: create audio device: " << this->DeviceName << std::endl;
        }

        this->context = alcCreateContext(this->device, nullptr);

        if (!this->context)
        {
            throw Coders(25);
        }

        if (CORE_INFO)
        {
            console::printTime();
            std::cout << "Ok: create audio context" << std::endl;
        }
    }


    audio::Device::~Device()
    {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(this->context);
        alcCloseDevice(this->device);
    }

    audio::Device audio::Device::init()
    {

        return audio::Device();
    }

    audio::Device *audio::Device::ptrInit()
    {
        return new audio::Device();
    }

    std::string audio::Device::getStringAllDevice()
    {
        return std::string(alcGetString(NULL, ALC_ALL_DEVICES_SPECIFIER));
    }

    void audio::Device::setContext()
    {
        if (!alcMakeContextCurrent(this->context))
        {
            throw Coders(26);
        }
    }
}

