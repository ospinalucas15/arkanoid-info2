#ifndef BRICK_H
#define BRICK_H

#include <QGraphicsItem>
#include <QPainter>

class Brick : public QGraphicsItem {
public:
    Brick(qreal x, qreal y, const QColor &color);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    qreal posX, posY;
    QColor brickColor;
    qreal width, height;
};

#endif // BRICK_H
