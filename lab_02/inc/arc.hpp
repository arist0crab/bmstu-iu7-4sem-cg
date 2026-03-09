#ifndef __ARC_HPP__
#define __ARC_HPP__


#include "status.hpp"
#include "shape.hpp"
#include <cmath>


class Arc : public Shape
{
    public:
        Arc(double x, double y, double radius, double start_angle, double end_angle, bool filling = false, QColor color = Qt::black) : Shape(x, y, filling, color), radius(radius), start_angle(start_angle), end_angle(end_angle) 
        {
            // if (radius <= 0)
                // TODO

            normalize_angles();
        }

        status_t draw(QPainter &painter) const override
        {
            if (this->radius <= 0)
                return ERR_DRAW_PARAM;

            painter.save();
            painter.setPen(QPen(this->color, 1));
            painter.setBrush(this->filling ? QBrush(this->color) : Qt::NoBrush);

            if (this->filling)
                painter.drawPie(this->center.x() - this->radius, this->center.y() - this->radius, 2 * this->radius, 2 * this->radius, this->start_angle * 16, (this->end_angle - this->start_angle) * 16);
            else
                painter.drawArc(this->center.x() - this->radius, this->center.y() - this->radius, 2 * this->radius, 2 * this->radius, this->start_angle * 16, (this->end_angle - this->start_angle) * 16);

            painter.restore();

            return SUCCESS_CODE;
        }


        status_t rotate(const double angle) override
        {
            return rotate_around(this->center, angle);
        }


        status_t rotate_around(const QPointF &rotation_center, const double angle) override
        {
            if (this->radius <= 0)
                return ERR_ROTATE_PARAM;

            QPointF relative_center = this->center - rotation_center;
    
            double angle_rad = angle * M_PI / 180.0;
            double cos_a = cos(angle_rad);
            double sin_a = sin(angle_rad);
            
            double new_x = relative_center.x() * cos_a - relative_center.y() * sin_a;
            double new_y = relative_center.x() * sin_a + relative_center.y() * cos_a;
            
            this->center = rotation_center + QPointF(new_x, new_y);
            
            this->start_angle = fmod(this->start_angle + angle, 360.0);
            this->end_angle = fmod(this->end_angle + angle, 360.0);
            
            normalize_angles();
            
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

            double cx = this->center.x();
            double cy = this->center.y();
            this->center.setX(cx * kx);
            this->center.setY(cy * ky);
            
            this->radius *= sqrt(kx * kx + ky * ky);

            return SUCCESS_CODE;
        }

    private:
        double radius;
        double start_angle, end_angle;

        status_t normalize_angles()
        {
            start_angle = fmod(start_angle, 360.0);
            if (start_angle < 0) start_angle += 360.0;
            
            end_angle = fmod(end_angle, 360.0);
            if (end_angle < 0) end_angle += 360.0;
            
            if (end_angle <= start_angle && (end_angle - start_angle) < -180)
                end_angle += 360.0;

            return SUCCESS_CODE;
        }
};


#endif
