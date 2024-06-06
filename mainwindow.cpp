#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "player.h"
#include "ball.h"
#include "brick.h"
#include "score.h"
#include "lives.h"
#include <QRandomGenerator>
#include <QApplication>
#include <QMessageBox> // Para mostrar el mensaje de Game Over

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

    // Creación del tapiz
    auto background = QImage(":/imagenes/tapiz.png");
    auto scaledBack = background.scaled(1200, 800);
    ui->graphicsView->setBackgroundBrush(scaledBack);

    // Posiciones del marcador y el puntaje
    scene->addItem(score);
    score->setPos(850, 450);  // Ajustar la posición según sea necesario
    scene->addItem(lives);
    lives->setPos(850, 475);  // Ajustar la posición según sea necesario

    // Posición inicial del jugador
    scene->addItem(player);
    player->setInitialPosition(430, 575);

    // Posición inicial de la bola
    scene->addItem(bola);
    bola->setPos(player->getPosX() + 45, player->getPosY() - 25);  // Colocar la bola encima del jugador
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
    int cols = 6; // Filas y columnas de ladrillos
    qreal brickWidth = 110;
    qreal brickHeight = 30;
    qreal areaWidth = cols * brickWidth;  // Ancho del fondo azul
    qreal areaHeight = rows * brickHeight;  // Alto del fondo azul

    // Offset para que los ladrillos estén solo en la parte azul y no ocupen todo el papel tapiz
    qreal startX = 170;
    qreal startY = 185;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Colores aleatorios de los ladrillos
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

        // Borrar ladrillo después de colisionar
        for (Brick* brick : bricksToRemove) {
            scene->removeItem(brick);
            bricks.removeOne(brick);
            delete brick;
        }

        if (bricks.isEmpty()) {  // Condición de victoria
            qDebug() << "You Win!";
            QApplication::quit();  // Cerrar la ventana
        }

        if (bola->collidesWithItem(player)) {
            bola->setVelocity(bola->getVelX(), -bola->getVelY());
        } else if (bola->getPosY() > 800) {  // Condición de pérdida
            lives->decrease();
            if (lives->getLives() <= 0) {
                // Mostrar mensaje de Game Over y cerrar el juego
                qDebug() << "Game Over!";
                QMessageBox::information(this, "Game Over", "perdiste todas las vidas");
                QApplication::quit();  // Cerrar la aplicación
            } else {
                // Reposicionar la bola y el jugador
                bola->setPos(475, 580);
                player->setInitialPosition(430, 575);
                bola->setPos(player->getPosX() + 45, player->getPosY() - 25);  // Colocar la bola encima del jugador
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





