//
// Created by kisly on 14.08.2025.
//

#ifndef DESCRIPTOR_HPP
#define DESCRIPTOR_HPP

namespace core
{
    class Descriptor
    {
    protected:
        unsigned int id;

    public:
        virtual void bind() = 0;
        virtual unsigned int getId() = 0;
    };
}

#endif //DESCRIPTOR_HPP
