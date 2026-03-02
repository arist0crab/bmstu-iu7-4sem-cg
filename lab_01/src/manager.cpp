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

        case SAVE_RESULT:
            sc = save_json_to_file(result_points, request.filename);
            break;

        case ADD_NEW_POINT:
            sc = check_new_point_can_be_added(json_data, points, request.point, request.point_id);
            if (sc == SUCCESS_CODE)
                sc = add_point_to_points(points, request.point);
            if (sc == SUCCESS_CODE)
                sc = add_point_to_json(json_data, request.point, request.point_id);
            if (sc == SUCCESS_CODE)
                sc = table_add_point(request.table_widget, request.point, request.point_id);
            break;

        case CHANGE_POINT:
            sc = check_point_can_be_changed(json_data, points, request.point, request.point_id);
            if (sc == SUCCESS_CODE)
                sc = change_point_in_points(points, json_data, request.point_id, request.point);
            if (sc == SUCCESS_CODE)
                sc = change_point_in_json(json_data, request.point_id, request.point);
            if (sc == SUCCESS_CODE) 
                sc = change_point_in_table(request.table_widget, request.point, request.point_id);
            break;

        case DELETE_POINT:
            sc = check_point_can_be_deleted(json_data, request.point_id);
            if (sc == SUCCESS_CODE)
                sc = delete_point_from_points(points, json_data, request.point_id);
            if (sc == SUCCESS_CODE)
                sc = delete_point_from_json(json_data, request.point_id);
            if (sc == SUCCESS_CODE)
                sc = table_delete_point(request.table_widget, request.point_id);
            break;

        case FIND_SOLUTION:
            sc = find_the_most_rhombus(json_data, points, result_points);
            break;

        case DRAW_SCALED_SOLUTION:
            sc = draw_scaled_solution(request.scene, points, json_data, result_points);
            break;

        case DRAW_SOLUTION_ALL_POINTS:
            sc = draw_solution_all_points(request.scene, points, json_data, result_points);
            break;

        case FLUSH_POINTS_TO_TABLE:
            sc = table_flush_points(request.table_widget, points, json_data);
            break;

        case CLEAR_ALL:
            sc = draw_scene_reset(request.scene);
            if (sc == SUCCESS_CODE)
                sc = reset_table_widget(request.table_widget);
            if (sc == SUCCESS_CODE)
            {
                json_clear(json_data);
                points_clear(points);
            }
            break;
        
        default:
            sc = ERR_UNDEFINED;
            break;
    }

    return sc;
}