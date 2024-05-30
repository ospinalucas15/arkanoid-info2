#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "player.h"
#include "ball.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    player = new Player(10, 10);
    timer = new QTimer;
    bola = new Ball(475, 580);
    flag = false;

    scene->setSceneRect(0, 0, 1200, 800);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->resize(scene->width(), scene->height());
    this->resize(ui->graphicsView->width(), ui->graphicsView->height());

    //Agrego tapiz
    auto background = QImage(":/imagenes/tapiz.png");
    auto scaledBack = background.scaled(1200, 800);
    ui->graphicsView->setBackgroundBrush(scaledBack);

    scene->addItem(player);
    player->setInitialPosition(430, 575);

    scene->addItem(bola);

    timer->start(20);

    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarEscena);

}

MainWindow::~MainWindow()
{
    delete player;
    delete scene;
    delete ui;
}

void MainWindow::actualizarEscena(){
    scene->advance();

    if (flag == true){
        bola->move();
        bola->checkColisionBounds();
    }

    float velBallY = bola->getVelY();

    if (flag == true){
        if (bola->collidesWithItem(player)){
            bola->setVelocity(bola->getVelX(), -1*velBallY);
        }
    }

}

void MainWindow::keyPressEvent(QKeyEvent* event){

    if(player != nullptr){


        if((event->key() == Qt::Key_A) && (player->getPosX() > 169)){
            player->setPosX(player->getPosX()-20);

            if (flag == false){
                bola->setPosX(player->getPosX()+45);
            }
        }

        else if((event->key() == Qt::Key_D) && (player->getPosX() < 705)){
            player->setPosX(player->getPosX()+20);

            if (flag == false){
                bola->setPosX(player->getPosX()+45);
            }
        }
        
    }

    if(bola != nullptr){

        if(event->key() == Qt::Key_Space){
            bola->move();
            flag = true;
        }
    }
}
