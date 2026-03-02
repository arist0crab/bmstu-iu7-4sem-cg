#include "messages.hpp"


status_t show_status_message(const status_t status, QMainWindow *parent)
{
    switch (status)
    {
        case SUCCESS_CODE:
            break;

        case ERR_POINT_DOESNT_EXIST:
            QMessageBox::critical(parent, StatusMessage::ERR_POINT_DOESNT_EXIST_TITLE, StatusMessage::ERR_POINT_DOESNT_EXIST_TEXT);
            break;

        case ERR_TWO_POINTS_EQUAL:
            QMessageBox::critical(parent, StatusMessage::ERR_TWO_POINTS_EQUAL_TITLE, StatusMessage::ERR_TWO_POINTS_EQUAL_TEXT);
            break;

        case ERR_INVALID_POINT:
            QMessageBox::critical(parent, StatusMessage::ERR_INVALID_POINT_TITLE, StatusMessage::ERR_INVALID_POINT_TEXT);
            break;

        case ERR_EMPTY_POINTS:
            QMessageBox::critical(parent, StatusMessage::ERR_EMPTY_POINTS_TITLE, StatusMessage::ERR_EMPTY_POINTS_TEXT);
            break;

        case ERR_EMPTY_SCENE:
            QMessageBox::critical(parent, StatusMessage::ERR_EMPTY_SCENE_TITLE, StatusMessage::ERR_EMPTY_SCENE_TEXT);
            break;

        case ERR_UNDEFINED:
            QMessageBox::critical(parent, StatusMessage::ERR_UNDEFINED_TITLE, StatusMessage::ERR_UNDEFINED_TEXT);
            break;

        case ERR_FIGURE:
            QMessageBox::critical(parent, StatusMessage::ERR_FIGURE_TITLE, StatusMessage::ERR_FIGURE_TEXT);
            break;

        case ERR_TABLE:
            QMessageBox::critical(parent, StatusMessage::ERR_TABLE_TITLE, StatusMessage::ERR_TABLE_TEXT);
            break;

        case ERR_ARGS:
            QMessageBox::critical(parent, StatusMessage::ERR_ARGS_TITLE, StatusMessage::ERR_ARGS_TEXT);
            break;

        case ERR_FILE:
            QMessageBox::critical(parent, StatusMessage::ERR_FILE_TITLE, StatusMessage::ERR_FILE_TEXT);
            break;
        
        case ERR_DATA:
            QMessageBox::critical(parent, StatusMessage::ERR_DATA_TITLE, StatusMessage::ERR_DATA_TEXT);
            break;

        case ERR_IO:
        QMessageBox::critical(parent, StatusMessage::ERR_IO_TITLE, StatusMessage::ERR_IO_TEXT);
            break;
    }

    return SUCCESS_CODE;
}