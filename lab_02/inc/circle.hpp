#ifndef __POLYGON_HPP__
#define __POLYGON_HPP__

#include "status.hpp"
#include "shape.hpp"

class Circle : public Shape
{
    public:
        Circle(double x, double y, double radius) : Shape(x, y), radius(radius) {}

        status_t draw() const override
        {
            // TODO
            return SUCCESS_CODE;
        }

        status_t rotate(const double angle) override
        {
            return SUCCESS_CODE;
        }

        status_t move(const double dx, const double dy) override
        {
            // TODO
            return SUCCESS_CODE;
        }

        status_t scale(const double kx, const double ky) override
        {
            // TODO
            return SUCCESS_CODE;
        }

    private:
        double radius;
};

#endif