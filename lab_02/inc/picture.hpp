#ifndef __PICTURE_HPP__
#define __PICTURE_HPP__

#include "status.hpp"
#include "shape.hpp"
#include <memory>


class Picture : public Shape
{
    public: 
        Picture(double x = 0, double y = 0) : Shape(x, y) {}
        ~Picture() {};

        status_t add_shape(std::unique_ptr<Shape> shape_ptr)
        {
            if (!shape_ptr) 
                return ERR_SHAPE_PARAM;

            shapes.push_back(std::move(shape_ptr));
            
            return SUCCESS_CODE;
        }

        status_t draw(QPainter &painter) const override
        {
            for (const auto &shape : this->shapes)
                shape->draw(painter);    

            return SUCCESS_CODE;
        }

        status_t rotate(const double angle) override
        {
            for (const auto &shape : this->shapes)
                shape->rotate(angle);

            return SUCCESS_CODE;
        }

        status_t move(const double dx, const double dy) override
        {
            for (const auto &shape : this->shapes)
                shape->move(dx, dy);

            return SUCCESS_CODE;
        }

        status_t scale(const double kx, const double ky) override
        {
            if (kx <= 0 || ky <= 0)
                return ERR_SCALE_PARAM;

            for (const auto &shape : this->shapes)
                shape->scale(kx, ky);
            
            return SUCCESS_CODE;
        }

    private:
        std::vector<std::unique_ptr<Shape>> shapes;
};

#endif