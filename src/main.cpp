#include <QApplication>


#include "base/ApplicationController.h"
#include "base/AccountManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ApplicationController ac(&a);
    
    ac.connect(&a, &QApplication::aboutToQuit, &ac, &ApplicationController::quit);
    ac.connect(&ac, &ApplicationController::terminated, &QApplication::quit);
    
    return a.exec();
}
