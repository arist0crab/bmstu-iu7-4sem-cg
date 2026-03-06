#ifndef __BEZIER_CURVE_HPP__
#define __BEZIER_CURVE_HPP__

#include "status.hpp"
#include "shape.hpp"
#include <vector>
#include <QPainterPath>

class BezierCurve : public Shape
{
    public:
        BezierCurve(const std::vector<QPointF> &points) : Shape(0, 0), path() 
        {
            // TODO
        }

        status_t draw() const override
        {
            // TODO
            return SUCCESS_CODE;
        }

        status_t rotate(const double angle) override
        {
            return SUCCESS_CODE;
        }

        status_t move(const double dx, const double dy) override
        {
            // TODO
            return SUCCESS_CODE;
        }

        status_t scale(const double kx, const double ky) override
        {
            // TODO
            return SUCCESS_CODE;
        }

    private:
        QPainterPath path;

};

#endif