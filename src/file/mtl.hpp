//
// Created by kisly on 16.07.2025.
//

#ifndef MTL_HPP
#define MTL_HPP

#include <string>
#include <vector>

namespace core
{
    class mtl
    {
    private:
        std::string code = "";
        std::string info = "";
        std::vector<std::string> namesResourcesGroups = {};

        mtl(const char* path);

    public:
        static mtl load(const char* path);
        static mtl *ptrLoad(const char* path);

        ~mtl();

        std::string getInfo();
        std::vector<std::string> getListMtlRes();
    };

}

#endif //MTL_HPP
