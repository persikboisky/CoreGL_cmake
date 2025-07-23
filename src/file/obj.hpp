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
        std::map<std::string, infoObject> objects = {};
        std::vector<std::string> listNamesObjects = {};
        
        void read(const char *path);

        obj(const char *path);

    public:
        static obj load(const char *path);
        static obj *ptrLoad(const char *path);

        std::vector<std::string> getListNamesObjects();
        std::map<std::string, infoObject> getObjects();
    };
}

#endif //OBJ_HPP
