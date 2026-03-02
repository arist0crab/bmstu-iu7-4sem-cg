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

status_t reset_table_widget(table_widget_t &table_widget);
status_t table_flush_points(table_widget_t &table_widget, const points_t &points, const json_t &json_data);
status_t table_add_point(table_widget_t &table_widget, const point_t &point, const unsigned int point_id);
status_t change_point_in_table(table_widget_t &table_widget, const point_t &point, const size_t point_id);
status_t table_delete_point(table_widget_t &table_widget, const unsigned int point_id);

#endif