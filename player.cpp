#include "player.h"

Player::Player(qreal x, qreal y) {

    rowPixmap = 0;
    colPixmap = 0;
    width = 115;
    heigth = 69;
    stripe = new QPixmap(":/imagenes/platform.png");
    posX = x;
    posY = y;
}

QRectF Player::boundingRect() const{
    return QRectF(0, 0, width, heigth);
}

void Player::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
    QPixmap scaled = stripe->scaled(QSize(115, 69));
    painter->drawPixmap(0, 0, scaled, colPixmap, rowPixmap, width, heigth);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Player::setInitialPosition(qreal a, qreal b){
    setPosX(a);
    setPosY(b);
    setPos(getPosX(), getPosY());
}

qreal Player::getPosX(){
    return posX;
}

qreal Player::getPosY(){
    return posY;
}

void Player::setPosX(qreal x){
    posX = x;
}

void Player::setPosY(qreal y){
    posY = y;
}

void Player::advance(int phase){
    setPos(getPosX(), getPosY());
    Q_UNUSED(phase);
}