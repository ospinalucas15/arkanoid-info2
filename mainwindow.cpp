#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);

    scene->setSceneRect(0, 0, 810, 856);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->resize(scene->width()+2, scene->height()+2);
    this->resize(ui->graphicsView->width()+100, ui->graphicsView->height()+100);

    //Agrego tapiz
    auto background = QImage(":/imagenes/tapiz.png");
    ui->graphicsView->setBackgroundBrush(background);
}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}
