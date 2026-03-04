#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__

#include "status.hpp"

class Shape
{
    public:
        virtual status_t draw() const = 0;
        virtual ~Shape() {}
};

#endif