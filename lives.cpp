#include "lives.h"
#include <QFont>

Lives::Lives(QGraphicsItem *parent) : QGraphicsTextItem(parent), lives(2) {
    // Inicializar el texto de las vidas
    setPlainText(QString("Lives: ") + QString::number(lives));
    setDefaultTextColor(Qt::white);
    setFont(QFont("times", 16));
}

void Lives::decrease() {
    if (lives > 0) {
        lives--;
        setPlainText(QString("Lives: ") + QString::number(lives));
    }
}

int Lives::getLives() const {
    return lives;
}

