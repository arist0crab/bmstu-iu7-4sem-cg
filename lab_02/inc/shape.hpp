#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__

#include "status.hpp"
#include <QPointF>


class Shape
{
    public:
        Shape(double x, double y) : center(x, y) {};
        virtual ~Shape() {};

        virtual status_t draw() const = 0;
        virtual status_t rotate(const double angle) = 0;
        virtual status_t move(const double dx, const double dy) = 0;
        virtual status_t scale(const double kx, const double ky) = 0;

        status_t set_center(const QPointF &point) { center = point; }

    private:
        QPointF center;
};

#endif