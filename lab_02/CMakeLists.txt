cmake_minimum_required(VERSION 3.16)
project(gui_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)  # автоматические моки
set(CMAKE_AUTOUIC ON)  # автоматические юики

find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS inc/*.hpp)
file(GLOB UI_FILES forms/*.ui)

add_executable(gui_app ${SOURCES} ${HEADERS} ${UI_FILES})

set_target_properties(gui_app PROPERTIES
    AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/forms
)

target_include_directories(gui_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)

target_link_libraries(gui_app PRIVATE Qt6::Widgets)