#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QBuffer>

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
    enum class TabIndex
    {
        menuTab,
        settingsTab,
        gameTab
    };
    void startButtonClicked();
    void settingsButtonClicked();
    void settingsTabBackButtonClicked();
    void gameTabBackButtonClicked();
    void botTurnSliderMoved(int value);
    void volumeSliderMoved(int value);
    void Draw(const Match &f);
    Ui::MainWindow *ui;
    GraphicsScene *scene;
    QMediaPlayer *player;
    QBuffer *soundBuffer;
    QPixmap fieldPixmap;
    QPixmap whitePixmap;
    QPixmap blackPixmap;
    Player *p1, *p2;
    Match f;
    int botTurnTime;

public slots:
    void processTurn(Player *currentPlayer, Position p);
};
#endif // MAINWINDOW_H
