#ifndef LIVES_H
#define LIVES_H

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>

class Lives : public QGraphicsTextItem {
public:
    Lives(QGraphicsItem *parent = nullptr);

    void decrease();
    int getLives() const;

private:
    int lives;
};

#endif // LIVES_H
