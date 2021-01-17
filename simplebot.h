#ifndef SIMPLEBOT_H
#define SIMPLEBOT_H

#include <QRandomGenerator>
#include <QVector>
#include <QTimer>

#include "player.h"
#include "match.h"

using namespace std;

class SimpleBot : public Player
{
    CellState color;
public:
    SimpleBot();

    void setColor(CellState);
    CellState getColor();
    QString name();

    void processClick(Position);
    void turnStart(Match);
};

#endif // SIMPLEBOT_H
