#include "json_process.hpp"

static status_t write_json_to_file(const QJsonArray &jsonArray, const char *filename);
static status_t convert_quad_to_qjsonarray(const quadrilateral_t &quad, QJsonArray &json_array);
static status_t find_point_index_from_id(ssize_t &point_index, const json_t &json_data, const size_t changed_point_id);

status_t add_point_to_json(json_t &json_data, const point_t &new_point, const size_t new_point_id)
{
    json_t new_json_point = {
        { "id", new_point_id },
        { "x", new_point.x() },
        { "y", new_point.y() }
    };

    json_data.push_back(new_json_point);

    return SUCCESS_CODE;
}

status_t change_point_in_json(json_t &json_data, const size_t changed_point_id, const point_t &changed_point)
{
    status_t sc = SUCCESS_CODE;
    ssize_t point_index = -1;
    const double new_x = changed_point.x();
    const double new_y = changed_point.y();

    sc = find_point_index_from_id(point_index, json_data, changed_point_id);
    if (sc == SUCCESS_CODE)
    {
        json_data[point_index] = {
            { "id", changed_point_id },
            { "x", new_x },
            { "y", new_y }
        };
    }

    return sc;
}

status_t delete_point_from_json(json_t &json_data, const size_t delete_point_id)
{
    status_t sc = SUCCESS_CODE;
    ssize_t point_index = -1;

    sc = find_point_index_from_id(point_index, json_data, delete_point_id);
    if (sc == SUCCESS_CODE)
        json_data.erase(json_data.begin() + point_index);

    return sc;
}

status_t save_json_to_file(const quadrilateral_t &quad, const char *filename)
{
    status_t sc = is_quadrilateral_valid(quad);
    QJsonArray json_array;

    if (sc == SUCCESS_CODE)
        sc = convert_quad_to_qjsonarray(quad, json_array);
    
    if (sc == SUCCESS_CODE)
        sc = write_json_to_file(json_array, filename);
    
    return sc;
}

status_t json_clear(json_t &json_data)
{
    json_data.clear();
    return SUCCESS_CODE;
}

static status_t find_point_index_from_id(ssize_t &point_index, const json_t &json_data, const size_t changed_point_id)
{
    status_t sc = SUCCESS_CODE;
    point_index = -1;

    for (size_t i = 0; point_index < 0 && i < json_data.size(); i++)
        if (json_data[i]["id"] == changed_point_id)
            point_index = i;

    if (point_index < 0) sc = ERR_POINT_DOESNT_EXIST;

    return sc;
}

static status_t write_json_to_file(const QJsonArray &jsonArray, const char *filename)
{
    status_t sc = SUCCESS_CODE;

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly))
        sc = ERR_FILE;
    
    if (sc == SUCCESS_CODE)
    {
        QJsonDocument doc(jsonArray);
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
    }
    
    return SUCCESS_CODE;
}


static status_t convert_quad_to_qjsonarray(const quadrilateral_t &quad, QJsonArray &json_array)
{
    json_array = QJsonArray();
    
    QJsonObject obj1;
    QJsonObject obj2;
    QJsonObject obj3;
    QJsonObject obj4;

    obj1["id"] = static_cast<int>(quad.i1);
    obj1["x"] = quad.p1.x();
    obj1["y"] = quad.p1.y();
    json_array.append(obj1);
    
    obj2["id"] = static_cast<int>(quad.i2);
    obj2["x"] = quad.p2.x();
    obj2["y"] = quad.p2.y();
    json_array.append(obj2);
    
    obj3["id"] = static_cast<int>(quad.i3);
    obj3["x"] = quad.p3.x();
    obj3["y"] = quad.p3.y();
    json_array.append(obj3);
    
    obj4["id"] = static_cast<int>(quad.i4);
    obj4["x"] = quad.p4.x();
    obj4["y"] = quad.p4.y();
    json_array.append(obj4);
    
    return SUCCESS_CODE;
}