#include <QApplication>
#include <QtWidgets>
#include <iostream>

#include "cityscape.h"
#include "citymotor.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Cityscape cityscape;
    cityscape.resize(1200,900);
    cityscape.show();
    return app.exec();
}
