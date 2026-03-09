#ifndef __POLYLINE_HPP__
#define __POLYLINE_HPP__

#include "status.hpp"
#include "shape.hpp"
#include <vector>
#include <cmath>


class Polyline : public Shape
{
    public:
        Polyline(const std::vector<QPointF> &points, bool filling = false, QColor color = Qt::black) : Shape(0, 0, filling, color), points(points) 
        {
            update_polyline_center();
        }

        status_t draw(QPainter &painter) const override
        {
            if (this->points.size() < 2)
                return ERR_DRAW_PARAM;

            painter.setPen(QPen(this->color));

            if (this->filling)
                draw_polygon(painter, this->points);
            else
                draw_polyline(painter, this->points);

            return SUCCESS_CODE;
        }

        status_t rotate(const double angle) override
        {
            return rotate_around(this->center, angle);
        }

        status_t rotate_around(const QPointF& rotation_center, const double angle) override
        {
            double cos_a = cos(angle);
            double sin_a = sin(angle);

            for (auto& point : points) {
                double x = point.x() - rotation_center.x();
                double y = point.y() - rotation_center.y();
                
                double x_new = x * cos_a - y * sin_a;
                double y_new = x * sin_a + y * cos_a;
                
                point.setX(rotation_center.x() + x_new);
                point.setY(rotation_center.y() + y_new);
            }
            
            update_polyline_center();
            return SUCCESS_CODE;
        }

        status_t move(const double dx, const double dy) override
        {
            for (auto& point : points) 
            {
                point.setX(point.x() + dx);
                point.setY(point.y() + dy);
            }
            
            center.setX(center.x() + dx);
            center.setY(center.y() + dy);
            
            return SUCCESS_CODE;
        }

        status_t scale(const double kx, const double ky) override
        {
            for (auto& point : points) 
            {
                double x = point.x() - center.x();
                double y = point.y() - center.y();
                
                point.setX(center.x() + x * kx);
                point.setY(center.y() + y * ky);
            }

            update_polyline_center();
            
            return SUCCESS_CODE;
        }

        // status_t scale_around(const QPointF& scale_center, const double kx, const double ky) override
        // {
        //     for (auto& point : points) 
        //     {
        //         double x = point.x() - scale_center.x();
        //         double y = point.y() - scale_center.y();
                
        //         point.setX(scale_center.x() + x * kx);
        //         point.setY(scale_center.y() + y * ky);
        //     }
            
        //     update_polyline_center();
        //     return SUCCESS_CODE;
        // }

    private:
        std::vector<QPointF> points;

        status_t draw_polygon(QPainter &painter, const std::vector<QPointF> &points) const
        {
            QPolygonF polygon;

            for (const auto &point : points)
                polygon << point;

            painter.setBrush(QBrush(this->color));
            painter.drawPolygon(polygon);

            return SUCCESS_CODE;
        }

        status_t draw_polyline(QPainter &painter, const std::vector<QPointF> &points) const
        {
            for (size_t i = 0; i < this->points.size() - 1; i++)
                painter.drawLine(this->points[i], this->points[i + 1]);
            
            return SUCCESS_CODE;
        }

        status_t update_polyline_center()
        {
            if (points.empty()) 
                center = QPointF(0, 0);
            else
            {
                double sum_x = 0, sum_y = 0;
                for (const auto& point : points) 
                {
                    sum_x += point.x();
                    sum_y += point.y();
                }
                
                center = QPointF(sum_x / points.size(), sum_y / points.size());
            }
            return SUCCESS_CODE;
        }
};

#endif