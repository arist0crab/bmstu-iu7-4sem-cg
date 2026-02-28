#include "io.hpp"

status_t get_json_from_file(const string &filename, json_t &json_data)
{
    status_t sc = SUCCESS_CODE;

    ifstream json_filestream(filename);

    if (!json_filestream.is_open())
        sc = ERR_FILE;

    if (sc == SUCCESS_CODE)
    {
        json_data = json_t::parse(json_filestream);
        json_filestream.close();
    }

    return sc;
}

status_t print_points_result(const quadrilateral_t &quad, json_t &json_result, const double eltime)
{
    json_result = { { "eltime", eltime }, { "result", { quad.i1, quad.i2, quad.i3, quad.i4 } } };
    cout << json_result << endl;

    return SUCCESS_CODE;
}   