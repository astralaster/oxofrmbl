#include <QApplication>
#include <QDebug>

#include "base/ApplicationController.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ApplicationController ac(&a);
    
    ac.connect(&ac, &ApplicationController::quit, &QApplication::quit);
    
    return a.exec();
}
