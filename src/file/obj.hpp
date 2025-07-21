//
// Created by kisly on 20.07.2025.
//

#ifndef OBJ_HPP
#define OBJ_HPP

#include <string>
#include <vector>
#include <map>

namespace core
{
    class img;

    struct infoObject 
    {
        float smoothingPoligons = 0;
        unsigned int texture = 0;
        std::vector<float> vertexes = {};
    };

    class obj
    {
    private:
        std::string comments = "";
        
        void read(const char *path);

        obj(const char *path);

    public:
        std::map<std::string, infoObject> objects = {};

        static obj load(const char *path);
        static obj *ptrLoad(const char *path);
    };
}

#endif //OBJ_HPP
