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
        StudentDeepseekov(const double canvas_width, const double canvas_height) : Picture(canvas_width, canvas_height)
        {
            build_student_deepseekov();
            move_picture_to_canvas_center(canvas_width, canvas_height);            
        }

    private:
        status_t build_student_deepseekov()
        {
            // тело
            this->add_shape(std::make_unique<Arc>(116.4, 148, 98, 169, 283, false, DEEPSEEKOV_SKIN));
            this->add_shape(std::make_unique<Arc>(153.4, 145.4, 134, 356, 175, false, DEEPSEEKOV_SKIN));

            // плавник
            this->add_shape(std::make_unique<Arc>(196, 238, 18, 124, 265, false, DEEPSEEKOV_SKIN));
            this->add_shape(std::make_unique<BezierCurve>(std::vector<QPointF>{ QPointF(138, 243), QPointF(163, 245), QPointF(170, 270), QPointF(194, 256) }, false, DEEPSEEKOV_SKIN));
            this->add_shape(std::make_unique<BezierCurve>(std::vector<QPointF>{ QPointF(256, 60), QPointF(324, 40), QPointF(246, 29), QPointF(236, 40) }, false, DEEPSEEKOV_SKIN));
            
            // линии хвоста и спины
            this->add_shape(std::make_unique<Ellipse>(261, 214, 23, 22, 0, false, DEEPSEEKOV_SKIN));
            this->add_shape(std::make_unique<Ellipse>(305, 203, 22, 22, 0, false, DEEPSEEKOV_SKIN));
            this->add_shape(std::make_unique<Arc>(311, 247, 23, 26, 97, false, DEEPSEEKOV_SKIN));
            this->add_shape(std::make_unique<Arc>(267, 252, 17, 90, 192, false, DEEPSEEKOV_SKIN));
            this->add_shape(std::make_unique<Polyline>(std::vector<QPointF>{ QPointF(239, 219), QPointF(244, 262), QPointF(251, 256) }, false, DEEPSEEKOV_SKIN));
            this->add_shape(std::make_unique<Polyline>(std::vector<QPointF>{ QPointF(332, 238), QPointF(344, 240), QPointF(327, 199) }, false, DEEPSEEKOV_SKIN));
            this->add_shape(std::make_unique<Polyline>(std::vector<QPointF>{ QPointF(287, 155), QPointF(292, 177), QPointF(310, 182) }, false, DEEPSEEKOV_SKIN));
            this->add_shape(std::make_unique<Polyline>(std::vector<QPointF>{ QPointF(247, 196), QPointF(262, 184), QPointF(258, 165), QPointF(186, 223) }, false, DEEPSEEKOV_SKIN));            
            // линии надбровной дуги
            this->add_shape(std::make_unique<Polyline>(std::vector<QPointF>{ QPointF(205, 142), QPointF(209, 127), QPointF(220, 120), QPointF(237, 119), QPointF(230, 139), QPointF(211, 159) }, false, DEEPSEEKOV_SPOTS));
            this->add_shape(std::make_unique<Arc>(202, 152, 13, 180, 307, false, DEEPSEEKOV_SPOTS));
            this->add_shape(std::make_unique<Arc>(194, 143, 12, 238, 359, false, DEEPSEEKOV_SPOTS));
            this->add_shape(std::make_unique<Ellipse>(194, 143, 4, 4, 0, false, DEEPSEEKOV_SPOTS));

            // пятно на пузике
            this->add_shape(std::make_unique<BezierCurve>(std::vector<QPointF>{ QPointF(139, 82), QPointF(178, 53) }, false, DEEPSEEKOV_SPOTS));
            this->add_shape(std::make_unique<BezierCurve>(std::vector<QPointF>{ QPointF(178, 53), QPointF(196, 35), QPointF(216, 46) }, false, DEEPSEEKOV_SPOTS));
            this->add_shape(std::make_unique<Arc>(134, 76, 8, 315, 135, false, DEEPSEEKOV_SPOTS));
            this->add_shape(std::make_unique<Ellipse>(121, 62, 12, 12, 0, false, DEEPSEEKOV_SPOTS));
            this->add_shape(std::make_unique<BezierCurve>(std::vector<QPointF>{ QPointF(116, 51), QPointF(50, 89), QPointF(37.4, 109), QPointF(46, 170) }, false, DEEPSEEKOV_SPOTS));
            this->add_shape(std::make_unique<BezierCurve>(std::vector<QPointF>{ QPointF(46, 170), QPointF(129, 170), QPointF(178, 53), QPointF(216, 46) }, false, DEEPSEEKOV_SPOTS));

            return SUCCESS_CODE;
        }
};

#endif