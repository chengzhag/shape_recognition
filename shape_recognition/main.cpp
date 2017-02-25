#include "shape_recognition.h"
#include "ui_mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShapeRecognition w;

    w.show();

    return a.exec();
}
