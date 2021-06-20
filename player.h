#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "match.h"

class Player : public QObject
{
    Q_OBJECT

public:
    virtual void setTurnTime(int miliseconds) = 0;
    virtual void setColor(CellState) = 0;
    virtual CellState getColor() = 0;
    virtual QString name() = 0;

public slots:
    virtual void turnStart(Match) = 0;
    virtual void processClick(Position) = 0; //for Human

signals:
    void turnFinished(Player*, Position);
};

#endif // PLAYER_H
