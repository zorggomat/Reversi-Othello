#ifndef MATCH_H
#define MATCH_H

#include <array>

#include "position.h"

class Match
{
    std::array<std::array<CellState, 8>, 8> field;
    inline void set(Position p, CellState newState);

    typedef Position (Position::*Direction)();
    std::array<Direction, 8> directions {&Position::up, &Position::upright, &Position::right, &Position::downright, &Position::down, &Position::downleft, &Position::left, &Position::upleft};
public:
    Match();
    Match(const Match& another);
    inline CellState get(Position p) const;
    bool makeTurn(Position p, CellState s, bool write = true);
    bool turnsAvailable(CellState type);
    unsigned count(CellState s) const;
};

#endif // MATCH_H
