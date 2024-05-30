#include "ball.h"

Ball::Ball(float px, float py){

    rowPixmap = 0;
    colPixmap = 0;
    width = 25;
    height = 25;
    stripe = new QPixmap(":/imagenes/ball.png");
    posX = px;
    posY = py;
    setPos(getPosX(), getPosY());

}


float Ball::getPosX(){
    return posX;
}

float Ball::getPosY(){
    return posY;
}

float Ball::getVelX(){
    return velX;
}

float Ball::getVelY(){
    return velY;
}

void Ball::setPosX(float a){
    posX = a;
    setPos(posX, posY);
}

void Ball::setVelocity(float a, float b){
    velX = a;
    velY = b;
}

void Ball::move(){
    posX += getVelX() * dt;
    posY += getVelY() * dt;

    setPos(getPosX(), getPosY());
}

void Ball::checkColisionBounds(){

    if (getPosX() < 169 || getPosX() > 790){

        setVelocity(-1*getVelX(), getVelY());
    }

    if (getPosY() < 50) {
        setVelocity(getVelX(), -1*getVelY());
    }
}


QRectF Ball::boundingRect() const{
    return QRectF(0, 0, width, height);
}

void Ball::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
    QPixmap scaled = stripe->scaled(QSize(25, 25));
    painter->drawPixmap(0, 0, scaled, colPixmap, rowPixmap, width, height);
    Q_UNUSED(option);
    Q_UNUSED(widget);

}
