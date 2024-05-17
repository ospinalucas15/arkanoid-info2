#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QTimer>

class Player : public QGraphicsItem{

    public:
        //constructor
        Player(qreal, qreal);

        QRectF boundingRect() const;
        void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
        void setInitialPosition(qreal a, qreal b);
        qreal getPosX();
        qreal getPosY();
        void setPosX(qreal);
        void setPosY(qreal);
        void advance(int);

    private:
        qreal posX, posY;
        QPixmap* stripe;
        qreal rowPixmap, colPixmap, width, heigth;
};


#endif // PLAYER_H
