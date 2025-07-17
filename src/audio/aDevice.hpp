//
// Created by kisly on 17.07.2025.
//

#ifndef ADEVICE_HPP
#define ADEVICE_HPP

#include <vector>
#include <string>

struct ALCdevice;
struct ALCcontext;

namespace core
{
    namespace audio
    {
        class Device
        {
        private:
            ALCdevice* device;
            ALCcontext* context;

            const char *DeviceName;

            Device();

        public:

            ~Device();

            static Device init();
            static Device* ptrInit();

            static std::string getStringAllDevice();

            void setContext();
        };
    }
}

#endif //ADEVICE_HPP
