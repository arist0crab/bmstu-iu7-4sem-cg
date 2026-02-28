#ifndef __TABLE_H__
#define __TABLE_H__

#include "status.hpp"
#include "geometry.hpp"
#include <QTableWidget>

typedef struct
{
    QTableWidget *table;
    size_t table_size;
} table_widget_t;

#endif