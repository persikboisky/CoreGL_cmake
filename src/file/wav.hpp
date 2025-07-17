//
// Created by kisly on 17.07.2025.
//

#ifndef WAV_HPP
#define WAV_HPP

#include <string>
#include <vector>

namespace core
{
    struct wavInfo
    {
        std::vector<char> data;
        std::string path;
        short channels;
        short bitsPerSample;
        short blockAlign;
        int sampleRate;
        int byteRate;
    };

    class wav
    {
    private:
        wavInfo info = {};

        wav(const char* path);

    public:
        ~wav();

        static std::vector<char> read(const char* path);

        static wav load(const char* path);
        static wav *ptrLoad(const char* path);

        wavInfo getInfo();
        short getChannels();
        short getBitsPerSample();
        int getSampleRate();
        std::vector<char> getData();
    };
}

#endif //WAV_HPP
