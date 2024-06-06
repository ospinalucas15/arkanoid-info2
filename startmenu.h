#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPalette>
#include <QBrush>

class StartMenu : public QWidget
{
    Q_OBJECT

public:
    explicit StartMenu(QWidget *parent = nullptr);
    ~StartMenu();

signals:
    void startGame();

private slots:
    void on_startButton_clicked();

private:
    QPushButton *startButton;
    QLabel *backgroundLabel;
};

#endif // STARTMENU_H
