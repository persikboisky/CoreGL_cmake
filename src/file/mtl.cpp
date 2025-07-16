//
// Created by kisly on 16.07.2025.
//

#include "mtl.hpp"
#include "code.hpp"

static void getResource(std::vector<std::string> &listMtlRes, std::string &info, std::string &mtlCode)
{
    for (unsigned int gElementID = 0; gElementID < mtlCode.size(); gElementID++)
    {
        // комментарий
        if (mtlCode[gElementID] == '#')
        {
            std::string comment = "";
            for (unsigned int elementID = gElementID + 1;; elementID++)
            {
                if (mtlCode[elementID] == '\n')
                {
                    comment += '\n';
                    gElementID = elementID;
                    break;
                }
                comment += mtlCode[elementID];
            }
            info += comment;
        }

        // считывание групп ресурсов
        else if (
                mtlCode[gElementID] == 'n' &&
                mtlCode[gElementID + 1] == 'e' &&
                mtlCode[gElementID + 2] == 'w'
        )
        {
            if (
                mtlCode[gElementID + 3] == 'm' &&
                mtlCode[gElementID + 4] == 't' &&
                mtlCode[gElementID + 5] == 'l'
            )
            {
                std::string nameMtlRes = "";
                for (unsigned int elementID = gElementID + 6;; elementID++)
                {
                    if (mtlCode[elementID] == ' ') continue;
                    if (mtlCode[elementID] == '\n')
                    {
                        listMtlRes.push_back(nameMtlRes);
                        break;
                    }

                    nameMtlRes += mtlCode[elementID];
                }
            }
        }
    }
}

core::mtl::mtl(const char *path)
{
    this->code = code::loadStr(path);
    getResource(this->namesResourcesGroups, this->info, this->code);
}

core::mtl core::mtl::load(const char *path)
{
    return core::mtl(path);
}

core::mtl *core::mtl::ptrLoad(const char *path)
{
    return new core::mtl(path);
}

core::mtl::~mtl()
{
    code.clear();
    namesResourcesGroups.clear();
}

std::string core::mtl::getInfo()
{
    return this->info;
}

std::vector<std::string> core::mtl::getListMtlRes()
{
    return this->namesResourcesGroups;
}

