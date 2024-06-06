#include "brick.h"

Brick::Brick(qreal x, qreal y, const QColor &color)
    : posX(x), posY(y), width(100), height(30), brickColor(color) {
    setPos(posX, posY);
}

QRectF Brick::boundingRect() const {
    return QRectF(0, 0, width, height);
}

void Brick::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setBrush(brickColor);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawRoundedRect(0, 0, width, height, 10, 10);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}


