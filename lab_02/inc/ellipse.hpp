#ifndef __ELLIPSE_HPP__
#define __ELLIPSE_HPP__

#include "status.hpp"
#include "shape.hpp"
#include <cmath>

class Ellipse : public Shape
{
    public:
        Ellipse(double x, double y, double rx, double ry, double rotation_angle, bool filling = false, QColor color = Qt::black) : Shape(x, y, filling, color), rx(rx), ry(ry), rotation_angle(rotation_angle) 
        {
            // if (rx <= 0 || ry <= 0)
                // TODO

            // if (rotation_angle)
        }

        status_t draw(QPainter &painter) const override
        {
            if (rx <= 0 || ry <= 0)
                return ERR_DRAW_PARAM;

            painter.save();
            painter.setPen(QPen(this->color, 1));
            painter.setBrush(this->filling ? QBrush(color) : Qt::NoBrush);

            QPolygonF ellipse_polygon;
            ellipse_approximation(ellipse_polygon);

            painter.drawPolygon(ellipse_polygon);
            painter.restore();

            return SUCCESS_CODE;
        }

        status_t rotate(const double angle) override
        {
            this->rotation_angle = fmod(this->rotation_angle + angle, 360);

            return SUCCESS_CODE;
        }

        status_t move(const double dx, const double dy) override
        {
            this->center.setX(this->center.x() + dx);
            this->center.setY(this->center.y() + dy);

            return SUCCESS_CODE;
        }

        status_t scale(const double kx, const double ky) override
        {
            if (kx <= 0 || ky <= 0)
                return ERR_SCALE_PARAM;

            this->rx *= kx;
            this->ry *= ky;

            return SUCCESS_CODE;
        }

    private:
        double rx, ry;
        double rotation_angle;

        status_t ellipse_approximation(QPolygonF &polygon) const
        {
            const size_t STEPS = 360;
            double angle_radians = this->rotation_angle * M_PI / 180.0;

            polygon.clear();
            polygon.reserve(STEPS);

            for (size_t i = 0; i < STEPS; i++)
            {
                double theta = 2 * M_PI * i / STEPS;

                double x = rx * cos(theta);
                double y = ry * sin(theta);

                double xr = x * cos(angle_radians) - y * sin(angle_radians);
                double yr = x * sin(angle_radians) + y * cos(angle_radians);

                polygon << QPointF(this->center.x() + xr, this->center.y() + yr);
            }

            return SUCCESS_CODE;
        }
};

#endif