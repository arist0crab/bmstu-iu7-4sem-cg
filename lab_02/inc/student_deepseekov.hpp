#ifndef __STUDENT_DEEPSEEKOV_HPP__
#define __STUDENT_DEEPSEEKOV_HPP__

#include "status.hpp"
#include "ellipse.hpp"
#include "polyline.hpp"
#include "arc.hpp"
#include "bezier_curve.hpp"
#include "picture.hpp"
#include <QColor>

static const QColor DEEPSEEKOV_SKIN(78, 108, 253);
static const QColor DEEPSEEKOV_SPOTS(255, 255, 255);

class StudentDeepseekov : public Picture
{
    public:
        StudentDeepseekov(double x, double y, double scale = 1.0) : Picture(x, y)
        {
            build_student_deepseekov();
        }

    private:
        status_t build_student_deepseekov()
        {
            // тело
            this->add_shape(std::make_unique<Arc>(58.2, 74, 48.5, 152, 288, true, DEEPSEEKOV_SKIN));
            this->add_shape(std::make_unique<Arc>(76.7, 72.7, 67, 356, 175, true, DEEPSEEKOV_SKIN));

            // плавник
            this->add_shape(std::make_unique<Arc>(97.5, 118, 9, 124, 265, false, DEEPSEEKOV_SKIN));
            this->add_shape(std::make_unique<BezierCurve>(std::vector<QPointF>{ QPointF(72, 122), QPointF(81.5, 122), QPointF(93, 131), QPointF(99, 124.5) }, false, DEEPSEEKOV_SKIN));
            this->add_shape(std::make_unique<BezierCurve>(std::vector<QPointF>{ QPointF(128, 30), QPointF(162, 20), QPointF(123, 14.5), QPointF(118, 20) }, true, DEEPSEEKOV_SKIN));
            
            // линии хвоста и спины
            this->add_shape(std::make_unique<Ellipse>(130, 107, 11, 11, 0, true, DEEPSEEKOV_SKIN));
            this->add_shape(std::make_unique<Ellipse>(152.5, 101.5, 11, 11, 0, true, DEEPSEEKOV_SKIN));
            this->add_shape(std::make_unique<Arc>(155.5, 123.5, 11.5, 26, 97, false, DEEPSEEKOV_SKIN));
            this->add_shape(std::make_unique<Arc>(133.5, 127, 8.5, 90, 186, false, DEEPSEEKOV_SKIN));
            this->add_shape(std::make_unique<Polyline>(std::vector<QPointF>{ QPointF(119.5, 109.5), QPointF(122, 131), QPointF(125.5, 128) }, false, DEEPSEEKOV_SKIN));
            this->add_shape(std::make_unique<Polyline>(std::vector<QPointF>{ QPointF(166, 119), QPointF(172, 120), QPointF(163.5, 99.5) }, false, DEEPSEEKOV_SKIN));
            this->add_shape(std::make_unique<Polyline>(std::vector<QPointF>{ QPointF(143, 79), QPointF(146, 88.5), QPointF(155, 91) }, false, DEEPSEEKOV_SKIN));
            this->add_shape(std::make_unique<Polyline>(std::vector<QPointF>{ QPointF(123.5, 98), QPointF(131, 92), QPointF(129, 82.5), QPointF(93, 111.5) }, false, DEEPSEEKOV_SKIN));
            
            // линии надбровной дуги
            this->add_shape(std::make_unique<Polyline>(std::vector<QPointF>{ QPointF(102.5, 71), QPointF(104.5, 63.5), QPointF(110, 60), QPointF(118.5, 59.5), QPointF(115, 69.5), QPointF(105.5, 79.5) }, false, DEEPSEEKOV_SPOTS));
            this->add_shape(std::make_unique<Arc>(101, 76, 6.5, 180, 307, false, DEEPSEEKOV_SPOTS));
            this->add_shape(std::make_unique<Arc>(97, 71.5, 6, 238, 359, false, DEEPSEEKOV_SPOTS));
            this->add_shape(std::make_unique<Ellipse>(97, 71.5, 2, 2, 0, true, DEEPSEEKOV_SPOTS));

            // пятно на пузике
            this->add_shape(std::make_unique<BezierCurve>(std::vector<QPointF>{ QPointF(69.5, 40.5), QPointF(89, 26.5) }, false, DEEPSEEKOV_SPOTS));
            this->add_shape(std::make_unique<BezierCurve>(std::vector<QPointF>{ QPointF(89, 26.5), QPointF(98, 17.5), QPointF(108, 23) }, true, DEEPSEEKOV_SPOTS));
            this->add_shape(std::make_unique<Arc>(67, 38, 4, 315, 135, false, DEEPSEEKOV_SPOTS));
            this->add_shape(std::make_unique<Ellipse>(60.5, 31, 6, 6, 0, true, DEEPSEEKOV_SPOTS));
            this->add_shape(std::make_unique<BezierCurve>(std::vector<QPointF>{ QPointF(58, 26), QPointF(25, 44.5), QPointF(18.7, 54.5), QPointF(23, 85) }, true, DEEPSEEKOV_SPOTS));
            this->add_shape(std::make_unique<BezierCurve>(std::vector<QPointF>{ QPointF(23, 85), QPointF(64.5, 85), QPointF(89, 26.5), QPointF(108, 23) }, false, DEEPSEEKOV_SPOTS));

            return SUCCESS_CODE;
        }
};

#endif