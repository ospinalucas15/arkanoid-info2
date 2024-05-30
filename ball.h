#ifndef BALL_H
#define BALL_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QTimer>


class Ball : public QGraphicsItem {

public:
    Ball(float px, float py);

    float getPosX();
    float getPosY();

    float getVelX();
    float getVelY();

    void setPosX(float a);
    void setVelocity(float a, float b);

    void move();
    void checkColisionBounds();

    QRectF boundingRect() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

private:

    float posX;
    float posY;
    float velX = 50;
    float velY = 50;

    const float widthCollision = 5;
    const float heightCollision = 5;
    const float horlimit = 700;
    const float verlimit = 700;
    const float dt = 0.1;

    QPixmap* stripe = nullptr;
    qreal rowPixmap, colPixmap, width, height;

};
#endif // BALL_H
