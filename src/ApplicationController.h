#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include <QApplication>

#include "gui/ContactListWindow.h"

class ApplicationController : QObject
{
    Q_OBJECT
public:
    ApplicationController(int argc, char *argv[]);
    int exec();

private:
    ContactListWindow clw;
    QApplication a;
};

#endif // APPLICATIONCONTROLLER_H
