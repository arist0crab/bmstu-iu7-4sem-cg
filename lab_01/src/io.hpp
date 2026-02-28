#ifndef __READ_JSON_HPP__
#define __READ_JSON_HPP__

#include "status.hpp"
#include "json.hpp"
#include "geometry.hpp"
#include <fstream>
#include <iostream>
using namespace std;

status_t get_json_from_file(const string &filename, json_t &json_data);
status_t print_points_result(const quadrilateral_t &quad, json_t &json_result, const double eltime);

#endif