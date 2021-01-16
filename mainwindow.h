#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "QGraphicsPixmapItem"

#include "player.h"
#include "match.h"
#include "human.hpp"
#include "advancedbot.h"
#include "simplebot.h"
#include "graphicsscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void startButtonClicked();
    void backButtonClicked();
    void Draw(const Match &f);
    Ui::MainWindow *ui;
    GraphicsScene *scene;
    QPixmap fieldPixmap;
    QPixmap whitePixmap;
    QPixmap blackPixmap;
    Player *p1, *p2;
    Match f;

public slots:
    void processTurn(Player *currentPlayer, Position p);
};
#endif // MAINWINDOW_H
