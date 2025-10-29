#include <QApplication>
#include "MainWindow.h"
#include <ElaApplication.h>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    ElaApplication::getInstance()->init();
    MainWindow w;
    w.show();
    return app.exec();
}
