#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QVector>
#include "player.h"
#include "ball.h"
#include "brick.h"
#include "score.h"
#include "lives.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* );
    bool flag;

public slots:
    void actualizarEscena();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene = nullptr;
    Player* player = nullptr;
    QTimer* timer = nullptr;
    Ball* bola = nullptr;
    QVector<Brick*> bricks;
    Score* score;
    Lives* lives;

    void createBricks();

    int xOffset = 170; // Offset en X del papel tapiz
    int yOffset = 710; // Offset en Y del papel tapiz

};
#endif // MAINWINDOW_H
