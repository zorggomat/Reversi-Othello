#ifndef HUMAN_HPP
#define HUMAN_HPP

#include "player.h"
#include "match.h"
#include "graphicsscene.h"

using namespace std;

class Human : public Player
{
    CellState color;
    GraphicsScene *scene;
public:
    Human(GraphicsScene *s)
    {
        scene = s;
    }

    void setTurnTime(int miliseconds)
    {
        Q_UNUSED(miliseconds);
    }

    void setColor(CellState c)
    {
        color = c;
    }

    CellState getColor()
    {
        return color;
    }

    QString name()
    {
        return "Human";
    }

    void turnStart(Match)
    {
        connect(scene, SIGNAL(clicked(Position)), this, SLOT(processClick(Position)));
    }

    void processClick(Position p)
    {
        disconnect(scene, SIGNAL(clicked(Position)), this, SLOT(processClick(Position)));
        emit turnFinished(this, p);
    }
};


#endif // HUMAN_HPP
