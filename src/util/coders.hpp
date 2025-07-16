//
// Created by kisly on 13.07.2025.
//

#ifndef CODERS_HPP
#define CODERS_HPP

#include <string>

namespace core
{
    class coders
    {
    private:
        std::string  info;
        int code;

    public:
        coders(int codeError, std::string addInfo = "");

        [[nodiscard]] int getCode() const;
        [[nodiscard]] std::string getInfo();

        void print();
    };
}

#endif //CODERS_HPP
