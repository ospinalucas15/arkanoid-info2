#include "startmenu.h"

StartMenu::StartMenu(QWidget *parent) : QWidget(parent)
{
    // Configurar la dimensión del widget
    this->setFixedSize(496, 680);

    // Configurar la imagen de fondo
    backgroundLabel = new QLabel(this);
    QPixmap backgroundPixmap(":/imagenes/background.png"); // Ruta de la imagen del fondo
    backgroundLabel->setPixmap(backgroundPixmap);
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setGeometry(0, 0, 496, 680);

    // Configurar el botón de inicio con una imagen de fondo escalada
    startButton = new QPushButton(this);
    startButton->setText("Start Game");
    startButton->setGeometry(198, 600, 100, 50); // Posicionar el botón

    QPixmap startPixmap(":/imagenes/start.png"); // Ruta de la imagen del botón
    QIcon buttonIcon(startPixmap.scaled(startButton->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    startButton->setIcon(buttonIcon);
    startButton->setIconSize(startButton->size());
    startButton->setStyleSheet("QPushButton { border: none; }");

    connect(startButton, &QPushButton::clicked, this, &StartMenu::on_startButton_clicked);
}

StartMenu::~StartMenu()
{
}

void StartMenu::on_startButton_clicked()
{
    emit startGame();
}
