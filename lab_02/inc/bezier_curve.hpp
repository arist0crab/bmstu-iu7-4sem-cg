#ifndef __BEZIER_CURVE_HPP__
#define __BEZIER_CURVE_HPP__

#include "status.hpp"
#include "shape.hpp"
#include <vector>
#include <cmath>
#include <QPainterPath>

// #kos.ai.begin

class BezierCurve : public Shape
{
    public:
        BezierCurve(const std::vector<QPointF> &points, bool filling = false, QColor color = Qt::black) : Shape(0, 0, filling, color), points(points)
        {
            update_bezier_center();
            rebuild_path();
        }

        status_t draw(QPainter &painter) const override
        {
            if (this->points.size() < 2 || this->points.size() > 5)
                return ERR_DRAW_PARAM;

            painter.save();
            painter.setPen(QPen(this->color, 1));
            painter.setBrush(this->filling ? QBrush(this->color) : Qt::NoBrush);

            painter.drawPath(this->path);
            painter.restore();

            return SUCCESS_CODE;
        }

        status_t rotate(const double angle) override
        {
            return rotate_around(this->center, angle);
        }

        status_t rotate_around(const QPointF &rotation_center, const double angle) override
        {
            double angle_rad = angle * M_PI / 180.0;
            double cos_a = cos(angle_rad);
            double sin_a = sin(angle_rad);

            for (auto &point : this->points) 
            {
                double x = point.x() - rotation_center.x();
                double y = point.y() - rotation_center.y();
                
                double x_new = x * cos_a - y * sin_a;
                double y_new = x * sin_a + y * cos_a;
                
                point.setX(rotation_center.x() + x_new);
                point.setY(rotation_center.y() + y_new);
            }
            
            update_bezier_center();
            rebuild_path();
            
            return SUCCESS_CODE;
        }

        status_t move(const double dx, const double dy) override
        {
            for (auto &point : this->points) 
            {
                point.setX(point.x() + dx);
                point.setY(point.y() + dy);
            }
            
            this->center.setX(this->center.x() + dx);
            this->center.setY(this->center.y() + dy);
            
            rebuild_path();
            
            return SUCCESS_CODE;
        }

        status_t scale(const double kx, const double ky) override
        {
            if (kx <= 0 || ky <= 0)
                return ERR_SCALE_PARAM;

            for (auto &point : this->points) 
            {
                double x = point.x() - this->center.x();
                double y = point.y() - this->center.y();
                
                point.setX(this->center.x() + x * kx);
                point.setY(this->center.y() + y * ky);
            }

            update_bezier_center();
            rebuild_path();
            
            return SUCCESS_CODE;
        }

        status_t set_closed(bool closed)
        {
            this->closed = closed;
            rebuild_path();
            return SUCCESS_CODE;
        }

    private:
        std::vector<QPointF> points;
        QPainterPath path;
        bool closed = false;

        status_t rebuild_path()
        {
            if (this->points.size() < 2 || this->points.size() > 5)
                return ERR_BEZIER_BUILD;

            this->path = QPainterPath();
            this->path.moveTo(this->points[0]);
            
            switch (this->points.size())
            {
                case 2:
                    this->path.lineTo(this->points[1]);
                    break;
                    
                case 3:
                    this->path.quadTo(this->points[1], this->points[2]);
                    break;
                    
                case 4:
                    this->path.cubicTo(this->points[1], this->points[2], this->points[3]);
                    break;

                case 5:
                {
                    const QPointF &p0 = this->points[0];
                    const QPointF &p1 = this->points[1];
                    const QPointF &p2 = this->points[2];
                    const QPointF &p3 = this->points[3];
                    const QPointF &p4 = this->points[4];

                    QPointF mid = QPointF((p2.x() + p3.x()) / 2.0, (p2.y() + p3.y()) / 2.0);

                    this->path.moveTo(p0);
                    this->path.cubicTo(p1, p2, mid);
                    this->path.cubicTo(p2, p3, p4);
                    break;
                }
            }
            
            if (this->closed)
                this->path.closeSubpath();
            
            return SUCCESS_CODE;
        }

        status_t update_bezier_center()
        {
            if (this->points.empty())
            {
                this->center = QPointF(0, 0);
                return ERR_BEZIER_BUILD;
            }
            
            double sum_x = 0, sum_y = 0;
            for (const auto &point : this->points) 
            {
                sum_x += point.x();
                sum_y += point.y();
            }
            
            this->center = QPointF(sum_x / this->points.size(), sum_y / this->points.size());
            
            return SUCCESS_CODE;
        }
};

// #kos.ai.end

#endif
