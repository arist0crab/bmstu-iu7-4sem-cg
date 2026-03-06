#ifndef __STUDENT_DEEPSEEKOV_HPP__
#define __STUDENT_DEEPSEEKOV_HPP__

#include "status.hpp"
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
            // TODO собрать дипсикова
        }
};

#endif