#include "advancedbot.h"

AdvancedBot::AdvancedBot() { }
QString AdvancedBot::name() { return "AdvancedBot"; }
void AdvancedBot::setColor(CellState c) { color = c; }
CellState AdvancedBot::getColor() { return color; }
void AdvancedBot::processClick(Position) {} //for Human
void AdvancedBot::turnStart(Match input)
{
    turnNumber++;

    QVector<Position> best;
    unsigned bestScore = 0;

    for(char i  = 1; i <= 8; ++i)
        for(int j = 1; j <= 8; ++j)
        {
            Position p(j, i);
            Match n(input);
            if(n.get(p) == empty && n.makeTurn(p, getColor())) //Checking all available cells
            {
                unsigned score = input.count(getColor());

                //In early game play minimum and check the crosshairs
                if(turnNumber > midGameTurn)
                {
                    score = 45 - score;
                    for(char k  = 1; k <= 8; ++k) if(n.get(Position(4, k)) == getColor()) score++;
                    for(char k  = 1; k <= 8; ++k) if(n.get(Position(5, k)) == getColor()) score++;
                    for(int j = 1; j <= 8; ++j) if(n.get(Position(j, 4)) == getColor()) score++;
                    for(int j = 1; j <= 8; ++j) if(n.get(Position(j, 5)) == getColor()) score++;
                }

                //Corners
                if(n.get(Position(1, 8)) == getColor()) score += 5;
                if(n.get(Position(8, 8)) == getColor()) score += 5;
                if(n.get(Position(1, 1)) == getColor()) score += 5;
                if(n.get(Position(8, 1)) == getColor()) score += 5;

                if(score > bestScore)
                {
                    bestScore=score;
                    best.clear();
                    best.push_back(p);
                }
                else if (score == bestScore)
                    best.push_back(p);
            }
        }

    QTimer::singleShot(300, [this, best]() { emit turnFinished(this, best[rand()%best.size()]); } );
}
