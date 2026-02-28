#include "status.hpp"
#include "geometry.hpp"
#include "io.hpp"
#include <iostream>
#include <chrono>
using namespace std;

int main(int argc, char *argv[])
{
    status_t sc = SUCCESS_CODE;
    quadrilateral_t result_points;
    json_t json_data, json_result;
    points_t points;

    double elapsed_time = 0.0;
    
    if (argc != 2) sc = ERR_ARGS;

    if (sc == SUCCESS_CODE)
        sc = get_json_from_file(argv[1], json_data);

    if (sc == SUCCESS_CODE)
        sc = read_points_from_json(json_data, points);

    if (sc == SUCCESS_CODE)
    {
        auto start = chrono::high_resolution_clock::now();
        sc = find_the_most_rhombus(json_data, points, result_points);
        auto end = chrono::high_resolution_clock::now();
        elapsed_time = chrono::duration<double>(end - start).count();
    }

    if (sc == SUCCESS_CODE)
        print_points_result(result_points, json_result, elapsed_time);

    return sc;
}