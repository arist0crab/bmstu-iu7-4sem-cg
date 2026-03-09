#ifndef __STATUS_HPP__
#define __STATUS_HPP__

typedef enum
{
    SUCCESS_CODE,
    ERR_SHAPE_PARAM,
    ERR_DRAW_PARAM,
    ERR_SCALE_PARAM,
    ERR_ROTATE_PARAM,
    ERR_BEZIER_BUILD,
    ERR_UNDEFINED
} status_t;

#endif