#include "simplebot.h"

SimpleBot::SimpleBot() { }
void SimpleBot::setColor(CellState c) { color = c; }
CellState SimpleBot::getColor() { return color; }
QString SimpleBot::name() { return "Simple Bot"; }
void SimpleBot::turnStart(Match input)
{
    QVector<Position> best;
    unsigned max = 0;

    for(char i  = 1; i <= 8; ++i)
        for(int j = 1; j <= 8; ++j)
        {
            Position p(j, i);
            Match n(input);
            if(n.get(p) == empty && n.makeTurn(p, getColor()))  //Checking all available cells
            {
                unsigned profitCount = n.count(getColor());
                if(profitCount > max) //Selecting cells with best score after turn
                {
                    best.clear();
                    best.push_back(p);
                    max = profitCount;
                }
                else if(profitCount == max)
                    best.push_back(p);
            }
        }
    QTimer::singleShot(300, [this, best]() { emit turnFinished(this, best[rand()%best.size()]); } );
}
void SimpleBot::processClick(Position) {}
