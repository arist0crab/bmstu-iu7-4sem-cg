#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__

#include "status.hpp"
#include <QPainter>
#include <QPointF>
#include <QColor>
#include <QPen>


class Shape
{
    public:
        Shape(double x, double y,bool filling = false, QColor color = Qt::black) : center(x, y), color(color), filling(filling) {};
        virtual ~Shape() {};

        virtual status_t draw(QPainter &painter) const = 0;
        virtual status_t rotate(const double angle) = 0;
        virtual status_t move(const double dx, const double dy) = 0;
        virtual status_t scale(const double kx, const double ky) = 0;

        status_t set_center(const QPointF &point) 
        { 
            this->center = point; 

            return SUCCESS_CODE;
        }

    protected:
        QPointF center;
        QColor color;
        bool filling;
};

#endif