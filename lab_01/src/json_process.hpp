#ifndef __JSON_H__
#define __JSON_H__

#include "status.hpp"
#include "json_nlohmann.hpp"
#include "points.hpp"
#include "geometry.hpp"
#include <QJsonDocument>
#include <QVariant>
#include <QFile>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>

status_t json_clear(json_t &json_data);
status_t save_json_to_file(const quadrilateral_t &quad, const char *filename);
status_t delete_point_from_json(json_t &json_data, const size_t delete_point_id);
status_t add_point_to_json(json_t &json_data, const point_t &new_point, const size_t new_point_id);
status_t change_point_in_json(json_t &json_data, const size_t changed_point_id, const point_t &changed_point);

#endif