#ifndef ADVANCEDBOT_H
#define ADVANCEDBOT_H

#include <QTimer>
#include <QVector>
#include <QRandomGenerator>

#include "player.h"
#include "match.h"

using namespace std;

class AdvancedBot : public Player
{
    CellState color;
    int turnNumber=0;
    const int midGameTurn = 45;
public:
    AdvancedBot();

    void setColor(CellState c);
    CellState getColor();
    QString name();

    void turnStart(Match);
    void processClick(Position);
};

#endif // ADVANCEDBOT_H
