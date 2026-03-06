#ifndef __PICTURE_HPP__
#define __PICTURE_HPP__

#include "status.hpp"
#include "shape.hpp"

class Picture : public Shape
{
    public: 
        Picture(double x = 0, double y = 0) : Shape(x, y) {}

        status_t add_shape()
        {
            // TODO
            return SUCCESS_CODE;
        }

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
        // TODO
        // std::vector<std::unique_ptr<Shape>> shapes;
        std::vector<Shape> shapes;
};

#endif