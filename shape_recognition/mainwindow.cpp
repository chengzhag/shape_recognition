#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ShapeRecognition shapeRecognition;

    QObject::connect(ui->pushButtonCameraIn, SIGNAL(clicked()), &shapeRecognition, SLOT(openCamera()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
