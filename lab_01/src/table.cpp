#include "table.hpp"

status_t table_flush_points(table_widget_t &table_widget, const points_t &points)
{
    status_t sc = SUCCESS_CODE;

    if (points.empty()) return ERR_EMPTY_POINTS;

    reset_table_widget(table_widget);

    

}

static status_t reset_table_widget(table_widget_t &table_widget)
{
    table_widget.table->clear();
    table_widget.table_size = 0;

    return SUCCESS_CODE;
}