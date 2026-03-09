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
        // TODO надо сделать так, чтобы center рассчитывался при инициализации фигуры
        // если при инициализации нет фигур, то он должен переопределяться позже при появлении
        // новых фигур

        status_t add_shape(std::unique_ptr<Shape> shape_ptr)
        {
            if (!shape_ptr) 
                return ERR_SHAPE_PARAM;

            shapes.push_back(std::move(shape_ptr));

            // TODO пересчет центра
            
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
            return this->rotate_around(this->center, angle);
        }

        status_t rotate_around(const QPointF &rotation_center, const double angle) 
        {
            if (this->shapes.empty())
                return ERR_ROTATE_PARAM;

            for (auto &shape : this->shapes)
                shape->rotate_around(rotation_center, angle);

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