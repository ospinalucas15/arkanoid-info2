#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMainWindow>
#include<QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QVector>
#include "player.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    player = new Player(10, 10);

    scene->setSceneRect(0, 0, 810, 856);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->resize(scene->width()+2, scene->height()+2);
    this->resize(ui->graphicsView->width()+100, ui->graphicsView->height()+100);

    //Agrego tapiz
    auto background = QImage(":/imagenes/tapiz.png");
    ui->graphicsView->setBackgroundBrush(background);

    scene->addItem(player);
    player->setInitialPosition(550, 575); 

    timer = new QTimer;
    timer->start(20);

    connect(timer, &QTimer::timeout, this, &MainWindow::actualizar);

}

MainWindow::~MainWindow()
{
    delete player;
    delete scene;
    delete ui;
}

void MainWindow::actualizar(){
    scene->advance();
}

void MainWindow::keyPressEvent(QKeyEvent* event){

    if(player != nullptr){
        
        if(event->key() == Qt::Key_A){
            player->setPosX(player->getPosX()-20);
        }

        else if(event->key() == Qt::Key_D){
            player->setPosX(player->getPosX()+20);
        }
    }
}
