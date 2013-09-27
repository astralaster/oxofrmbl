#include "gui/ContactListWindow.h"

#include <QApplication>

#include "ApplicationController.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ApplicationController ac(&a);

    return a.exec();
}
