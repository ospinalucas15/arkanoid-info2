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

};
#endif // MAINWINDOW_H
