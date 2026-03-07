#ifndef __STUDENT_DEEPSEEKOV_HPP__
#define __STUDENT_DEEPSEEKOV_HPP__

#include "status.hpp"
#include "ellipse.hpp"
#include "picture.hpp"

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
            this->add_shape(std::make_unique<Ellipse>(200, 200, 80, 40, 45, Qt::blue));

            return SUCCESS_CODE;
        }
};

#endif