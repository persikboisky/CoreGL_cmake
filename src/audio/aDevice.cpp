//
// Created by kisly on 17.07.2025.
//

#include "aDevice.hpp"
#include "../config.hpp"
#include "../util/coders.hpp"
#include "../util/console.hpp"
#include <AL\al.h>
#include <AL/alc.h>
#include <vector>
#include <string>
#include <iostream>
#include <fcntl.h>

namespace core
{
    audio::Device::Device()
    {
        this->device = alcOpenDevice(nullptr);

        if (!this->device)
        {
            throw coders(24);
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
            throw coders(25);
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
            throw coders(26);
        }
    }
}

