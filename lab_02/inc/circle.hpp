#ifndef __CIRCLE_HPP__
#define __CIRCLE_HPP__

#include "status.hpp"
#include "shape.hpp"

class Circle : public Shape
{
    public:
        Circle(double x, double y, double radius, QColor color) : Shape(x, y, color), radius(radius) {}

        status_t draw(QPainter &painter, bool filling = false) const override
        {
            if (radius <= 0) 
                return ERR_SHAPE_PARAM;

            painter.save();
            painter.setPen(QPen(color, 1));

            bresenham_circle(painter, center.x(), center.y(), radius);           
            
            painter.restore();

            return SUCCESS_CODE;
        }

        status_t rotate(const double angle) override
        {
            // если покрутить круг, внезапно получится тот же круг
            return SUCCESS_CODE;
        }

        status_t move(const double dx, const double dy) override
        {
            center.setX(center.x() + dx);
            center.setY(center.y() + dy);

            return SUCCESS_CODE;
        }

        status_t scale(const double kx, const double ky) override
        {
            if (kx <= 0 || ky <= 0)
                return ERR_SCALE_PARAM;

            
            return SUCCESS_CODE;
        }

    private:
        double radius;

        // алгоритм Брезенхэма, краденный у индуса с ютуба
        status_t bresenham_circle(QPainter &painter, const double cx, const double cy, const double radius) const
        {
            double x = 0;
            double y = radius;
            double d = 3 - 2 * radius;

            while (x <= y)
            {
                draw_eight_circle_points(painter, cx, cy, x, y);

                if (d < 0)
                    d = d + 4 * x + 6;
                else 
                {
                    d = d + 4 * (x - y) + 10;
                    y--;
                }

                x++;
            }

            return SUCCESS_CODE;
        }

        status_t draw_eight_circle_points(QPainter &painter, const double x0, const double y0, const double x, const double y) const 
        {
            painter.drawPoint(QPointF(x0 + x, y0 + y));
            painter.drawPoint(QPointF(x0 - x, y0 + y));
            painter.drawPoint(QPointF(x0 + x, y0 - y));
            painter.drawPoint(QPointF(x0 - x, y0 - y));

            painter.drawPoint(QPointF(x0 + y, y0 + x));
            painter.drawPoint(QPointF(x0 - y, y0 + x));
            painter.drawPoint(QPointF(x0 + y, y0 - x));
            painter.drawPoint(QPointF(x0 - y, y0 - x));

            return SUCCESS_CODE;
        }
};

#endif