#include "manager.hpp"

status_t manager(request_t &request)
{
    status_t sc = SUCCESS_CODE;
    
    static quadrilateral_t result_points;
    static json_t json_data;
    static points_t points;

    switch (request.type)
    {
        case JSON_LOAD:
            sc = get_json_from_file(request.filename, json_data);
            if (sc == SUCCESS_CODE)
                sc = read_points_from_json(json_data, points);
            break;

        case FIND_SOLUTION:
            sc = find_the_most_rhombus(json_data, points, result_points);
            break;

        case DRAW_SCALED_SOLUTION:
            sc = draw_scaled_solution(points, result_points, request.scene);
            break;

        case DRAW_SOLUTION_ALL_POINTS:
            sc = draw_solution_all_points(points, result_points, request.scene);
            break;
        
        default:
            sc = ERR_UNDEFINED;
            break;
    }

    return sc;
}