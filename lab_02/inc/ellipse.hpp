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
            if (this->rx <= 0 || this->ry <= 0)
                return ERR_DRAW_PARAM;

            painter.save();
            painter.setPen(QPen(this->color, 1));
            painter.setBrush(this->filling ? QBrush(this->color) : Qt::NoBrush);

            QPolygonF ellipse_polygon;
            ellipse_approximation(ellipse_polygon);

            painter.drawPolygon(ellipse_polygon);
            painter.restore();

            return SUCCESS_CODE;
        }

        status_t rotate(const double angle) override
        {
            return rotate_around(this->center, angle);
        }


        status_t rotate_around(const QPointF &rotation_center, const double angle)  override
        {
            if (this->rx <= 0 || this->ry <= 0)
                return ERR_ROTATE_PARAM;

            QPointF relative_center = this->center - rotation_center;
    
            double angle_rad = angle * M_PI / 180.0;
            double cos_a = cos(angle_rad);
            double sin_a = sin(angle_rad);
            
            double new_x = relative_center.x() * cos_a - relative_center.y() * sin_a;
            double new_y = relative_center.x() * sin_a + relative_center.y() * cos_a;
            
            this->center = rotation_center + QPointF(new_x, new_y);
            
            rotation_angle = fmod(rotation_angle + angle, 360.0);
            
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