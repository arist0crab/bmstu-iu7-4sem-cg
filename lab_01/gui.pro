TEMPLATE = app
TARGET = app-gui-linux-x64
QT += core widgets gui

# Папки проекта
HEADERS_DIR = src
SOURCES_DIR = src
FORMS_DIR = src

# Пути для компиляции
INCLUDEPATH += $$HEADERS_DIR

# Файлы проекта
SOURCES += $$files($$SOURCES_DIR/*.cpp)
HEADERS += $$files($$HEADERS_DIR/*.hpp)
FORMS += $$files($$FORMS_DIR/*.ui)

SOURCES -= $$SOURCES_DIR/main_cli.cpp

# Папка для сборки
MOC_DIR = moc
UI_DIR = ui