#ifndef __MESSAGES_HPP__
#define __MESSAGES_HPP__

#include "status.hpp"
#include "messages_text.hpp"
#include <QMainWindow>
#include <QMessageBox>

status_t show_status_message(const status_t status, QMainWindow *parent);

#endif