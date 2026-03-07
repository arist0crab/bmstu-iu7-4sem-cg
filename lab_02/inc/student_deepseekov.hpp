#ifndef __STUDENT_DEEPSEEKOV_HPP__
#define __STUDENT_DEEPSEEKOV_HPP__

#include "status.hpp"
#include "ellipse.hpp"
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
            this->add_shape(std::make_unique<Ellipse>(200, 200, 80, 40, 45, true, DEEPSEEKOV_SKIN));

            return SUCCESS_CODE;
        }
};

#endif