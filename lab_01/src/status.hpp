#ifndef __STATUS_HPP__
#define __STATUS_HPP__

typedef enum
{
    SUCCESS_CODE,
    ERR_EMPTY_POINTS,
    ERR_EMPTY_SCENE,
    ERR_UNDEFINED,
    ERR_FIGURE,
    ERR_ARGS,
    ERR_FILE,
    ERR_DATA,
    ERR_IO
} status_t;

#endif