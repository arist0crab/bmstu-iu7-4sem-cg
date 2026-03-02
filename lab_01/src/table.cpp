#include "table.hpp"


static status_t table_add_item_to_row(table_widget_t &table_widget, const size_t col_index, const QVariant value);
static status_t table_change_item_by_point_id(table_widget_t &table_widget, const size_t point_id, const size_t col_index, const QVariant &value);
static status_t table_update_item_by_row(table_widget_t &table_widget, const size_t row_index, const size_t col_index, const QVariant &value);
static status_t table_create_new_row(table_widget_t &table_widget, const size_t row_index);
static status_t table_get_size(table_widget_t &table_widget, unsigned int &table_size);
static status_t table_increase_row_quantity(table_widget_t &table_widget);


status_t table_flush_points(table_widget_t &table_widget, const points_t &points, const json_t &json_data)
{
    if (points.empty()) return ERR_EMPTY_POINTS;

    reset_table_widget(table_widget);

    for (size_t i = 0; i < points.size(); i++)
        table_add_point(table_widget, points[i], json_data[i]["id"]);

    return SUCCESS_CODE;;

}

status_t table_delete_point(table_widget_t &table_widget, const unsigned int point_id)
{
    status_t sc = SUCCESS_CODE;
    bool point_found = false;

    for (unsigned i = 0; !point_found && i < table_widget.table_size; i++) 
    {
        QTableWidgetItem *idItem = table_widget.table->item(i, 0);
        if (idItem && idItem->text().toUInt() == point_id) 
        {
            point_found = true;
            table_widget.table->removeRow(i);
            table_widget.table_size--;
        }
    }

    if (!point_found) sc = ERR_POINT_DOESNT_EXIST;
    
    return sc;
}

status_t table_add_point(table_widget_t &table_widget, const point_t &point, const unsigned int point_id)
{
    unsigned int table_size;

    table_get_size(table_widget, table_size);
    table_create_new_row(table_widget, table_size);

    table_add_item_to_row(table_widget, 0, point_id);
    table_add_item_to_row(table_widget, 1, point.x());
    table_add_item_to_row(table_widget, 2, point.y());
    
    table_increase_row_quantity(table_widget);

    return SUCCESS_CODE;
}

static status_t table_add_item_to_row(table_widget_t &table_widget, const size_t col_index, const QVariant value)
{
    QTableWidgetItem *idItem = new QTableWidgetItem(value.toString());
    idItem->setTextAlignment(Qt::AlignCenter);
    table_widget.table->setItem(table_widget.table_size, col_index, idItem);

    return SUCCESS_CODE;
}

status_t change_point_in_table(table_widget_t &table_widget, const point_t &point, const size_t point_id)
{
    status_t sc = SUCCESS_CODE;

    sc = table_change_item_by_point_id(table_widget, point_id, 1, point.x());
    if (sc == SUCCESS_CODE)
        sc = table_change_item_by_point_id(table_widget, point_id, 2, point.y());

    return sc;
}

static status_t table_change_item_by_point_id(table_widget_t &table_widget, const size_t point_id, const size_t col_index, const QVariant &value)
{
    status_t sc = SUCCESS_CODE;
    bool row_founded = false;

    for (unsigned i = 0; !row_founded && i < table_widget.table_size; i++) 
    {
        QTableWidgetItem *idItem = table_widget.table->item(i, 0);
        if (idItem && idItem->text().toUInt() == point_id)
        {
            row_founded = true;
            sc = table_update_item_by_row(table_widget, i, col_index, value);
        }
    }

    if (!row_founded) sc = ERR_TABLE;
    
    return sc;
}

static status_t table_update_item_by_row(table_widget_t &table_widget, const size_t row_index, const size_t col_index, const QVariant &value)
{
    status_t sc = SUCCESS_CODE;
    QTableWidgetItem *item = nullptr;

    if (row_index >= table_widget.table_size)
        sc = ERR_TABLE;
    
    if (sc == SUCCESS_CODE)
    {
        item = table_widget.table->item(row_index, col_index);
        if (item == nullptr)
            sc = ERR_TABLE;
        else
        {
            item->setText(value.toString());
            item->setTextAlignment(Qt::AlignCenter);
        }
    }
    
    return sc;
}

static status_t table_create_new_row(table_widget_t &table_widget, const size_t row_index)
{
    table_widget.table->insertRow(row_index);

    return SUCCESS_CODE;
}

static status_t table_increase_row_quantity(table_widget_t &table_widget)
{
    table_widget.table_size++;

    return SUCCESS_CODE;
} 

static status_t table_get_size(table_widget_t &table_widget, unsigned int &table_size)
{
    table_size = table_widget.table_size;

    return SUCCESS_CODE;
}

status_t reset_table_widget(table_widget_t &table_widget)
{
    table_widget.table->setRowCount(0);
    table_widget.table_size = 0;

    return SUCCESS_CODE;
}