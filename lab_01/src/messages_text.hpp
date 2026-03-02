#ifndef __MESSAGES_TEXT_HPP__
#define __MESSAGES_TEXT_HPP__

namespace StatusMessage
{
    inline const char *ERR_POINT_DOESNT_EXIST_TITLE = "Точка не существует";
    inline const char *ERR_POINT_DOESNT_EXIST_TEXT = "Ошибка обработки данных: необходимая точка не была найдена";

    inline const char *ERR_TWO_POINTS_EQUAL_TITLE = "Две точки совпадают";
    inline const char *ERR_TWO_POINTS_EQUAL_TEXT = "Невозможно добавить/изменить точку: ее координаты совпадают с координатами уже существующей";

    inline const char *ERR_INVALID_POINT_TITLE = "Невалидная точка";
    inline const char *ERR_INVALID_POINT_TEXT = "Что-то пошло не так: невозможно обработать точку";

    inline const char *ERR_EMPTY_POINTS_TITLE = "Ни одной точки не существует";
    inline const char *ERR_EMPTY_POINTS_TEXT = "Невозможно выполнить операцию: массив точек пуст";

    inline const char *ERR_EMPTY_SCENE_TITLE = "Ошибка рисования";
    inline const char *ERR_EMPTY_SCENE_TEXT = "Холста для рисования не существует";

    inline const char *ERR_UNDEFINED_TITLE = "Неопределенная ошибка";
    inline const char *ERR_UNDEFINED_TEXT = "Мы тоже не знаем, что происходит";

    inline const char *ERR_FIGURE_TITLE = "Невалидная фигура";
    inline const char *ERR_FIGURE_TEXT = "Невозможно обработать невалидную фигуру";

    inline const char *ERR_TABLE_TITLE = "Ошибка работы с таблицей";
    inline const char *ERR_TABLE_TEXT = "Что-то пошло не так при работе с таблицей";

    inline const char *ERR_ARGS_TITLE = "Невалидные аргументы";
    inline const char *ERR_ARGS_TEXT = "Что-то пошло не так при работе с аргументами";

    inline const char *ERR_FILE_TITLE = "Ошибка обработки файла";
    inline const char *ERR_FILE_TEXT = "Что-то пошло не так при работе с файлами";

    inline const char *ERR_DATA_TITLE = "Ошибка обработки данных";
    inline const char *ERR_DATA_TEXT = "Что-то пошло не так при работе с данными";

    inline const char *ERR_IO_TITLE = "Ошибка ввода/вывода данных";
    inline const char *ERR_IO_TEXT = "Проверьте корректность используемых данных";
}

#endif