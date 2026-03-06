#ifndef __ARC_HPP__
#define __ARC_HPP__

#include "status.hpp"
#include "shape.hpp"

class Arc : public Shape
{
    public:
        Arc(double x, double y, double radius, double start_angle, double end_angle) : Shape(x, y), radius(radius), start_angle(start_angle), end_angle(end_angle) {}

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
        double start_angle, end_angle;
};

#endif