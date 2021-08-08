#include "match.h"
#include "mainwindow.h"
#include "QGraphicsScene"
#include "QGraphicsPixmapItem"

#include <array>

using namespace std;

inline void Match::set(Position p, CellState newState)
{
    field[p.X-1][p.Y-1] = newState;
}
Match::Match()
{
    //for_each(field.begin(), field.end(), bind2nd(mem_fun_ref(&array<CellState, 8>::fill), empty) );
    for(int i = 0; i < 8; ++i) field[i].fill(CellState::empty);
    field[3][3] = white;
    field[4][4] = white;
    field[3][4] = black;
    field[4][3] = black;
}
Match::Match(const Match& another)
{
    field = another.field;
}
bool Match::makeTurn(Position p, CellState s, bool write)
{
    if (!p.correct() || get(p) != CellState::empty || s == CellState::empty)
        return false;

    CellState enemy = ((s == black) ? white : black );
    bool hasSeq = false;

    for(Direction next : directions)
    {
        Position current = p;
        bool gotEnemy = false;
        while((current.*next)().correct())
        {
            if(get((current.*next)()) == enemy)
            {
                gotEnemy = true;
                current = (current.*next)();
            }
            else if(get((current.*next)()) == s)
            {
                if(!gotEnemy) break;
                hasSeq = true;
                if(write)
                {
                    set(p, s);
                    for(current = (p.*next)(); get(current) != s; current=(current.*next)())
                        set(current, s);
                }
                break;
            }
            else break;
        }
    }
    return hasSeq;
}
bool Match::turnsAvailable(CellState type)
{
    for(char i  = 1; i <= 8; ++i)
        for(int j = 1; j <= 8; ++j)
            if(get(Position(j, i)) == CellState::empty && makeTurn(Position(j, i), type, false))
                return true;
    return false;
}
unsigned Match::count(CellState s) const
{
    unsigned r = 0;
    for(char i  = 1; i <= 8; ++i)
        for(int j = 1; j <= 8; ++j)
            if(get(Position(j, i)) == s)
                ++r;
    return r;
}
