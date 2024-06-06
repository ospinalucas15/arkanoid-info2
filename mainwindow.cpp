#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "player.h"
#include "ball.h"
#include "brick.h"
#include "score.h"
#include "lives.h"
#include <QRandomGenerator>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    player = new Player(10, 10);
    timer = new QTimer;
    bola = new Ball(475, 580);
    score = new Score();
    lives = new Lives();
    flag = false;

    scene->setSceneRect(0, 0, 1200, 800);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->resize(scene->width(), scene->height());
    this->resize(ui->graphicsView->width(), ui->graphicsView->height());

    //creazcion del tapiz
    auto background = QImage(":/imagenes/tapiz.png");
    auto scaledBack = background.scaled(1200, 800);
    ui->graphicsView->setBackgroundBrush(scaledBack);

    //posiciones del marcador y el puntaje
    scene->addItem(score);
    score->setPos(850, 450);  // Ajustar la posición según sea necesario
    scene->addItem(lives);
    lives->setPos(850, 475);  // Ajustar la posición según sea necesario
    //posicion inicial del jugador
    scene->addItem(player);
    player->setInitialPosition(430, 575);

    scene->addItem(bola);
    qDebug() << "PosX: " << bola->getPosX() << " Pos Y: " << bola->getPosY();

    timer->start(20);
    createBricks();

    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarEscena);
}

MainWindow::~MainWindow()
{
    delete player;
    delete scene;
    delete ui;
}

void MainWindow::createBricks() {
    int rows = 5;
    int cols = 6; //filas y columnas de ladrillos
    qreal brickWidth = 110;
    qreal brickHeight = 30;
    qreal areaWidth = cols * brickWidth;  // ancho del fondo azul
    qreal areaHeight = rows * brickHeight;  // alto del fondo azul

    //offset para que los ladrillos esten solo en la parte azul y no ocupen todo el papel tapiz
    qreal startX = xOffset;
    qreal startY = yOffset - 525;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            //colores aleatorios de los ladrillos
            QColor color = QColor::fromRgb(QRandomGenerator::global()->generate());
            Brick* brick = new Brick(startX + j * brickWidth, startY + i * brickHeight, color);
            scene->addItem(brick);
            bricks.append(brick);
        }
    }
}

void MainWindow::actualizarEscena() {
    scene->advance();

    if (flag) {
        bola->move();
        bola->checkColisionBounds();

        QList<Brick*> bricksToRemove;

        for (Brick* brick : bricks) {
            if (bola->collidesWithItem(brick)) {
                bola->setVelocity(bola->getVelX(), -bola->getVelY());
                bricksToRemove.append(brick);
                score->increase(); // +1 cuando colisione un ladrillo
            }
        }

        //borrar ladrilo despues de colisiounar
        for (Brick* brick : bricksToRemove) {
            scene->removeItem(brick);
            bricks.removeOne(brick);
            delete brick;
        }

        if (bricks.isEmpty()) {  //condicion de victoria
            qDebug() << "You Win!";
            QApplication::quit();  //cerrar la venta
        }

        if (bola->collidesWithItem(player)) {
            bola->setVelocity(bola->getVelX(), -bola->getVelY());
        } else if (bola->getPosY() > 800) {  //condicion de perdida
            lives->decrease();
            if (lives->getLives() <= 0) {
                //cerrar el juego
                qDebug() << "Game Over!";
            } else {
                // Reposicionar la bola y el jugador
                bola->setPos(475, 580);
                player->setInitialPosition(430, 575);
                flag = false;
            }
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event) {

    if (player != nullptr) {
        if ((event->key() == Qt::Key_A) && (player->getPosX() > 169)) {
            player->setPosX(player->getPosX() - 20);
            if (!flag) {
                bola->setPosX(player->getPosX() + 45);
            }
        }
        else if ((event->key() == Qt::Key_D) && (player->getPosX() < 705)) {
            player->setPosX(player->getPosX() + 20);
            if (!flag) {
                bola->setPosX(player->getPosX() + 45);
            }
        }
    }

    if (bola != nullptr) {
        if (event->key() == Qt::Key_Space) {
            bola->move();
            flag = true;
        }
    }
}





