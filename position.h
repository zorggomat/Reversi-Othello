#ifndef POSITION_H
#define POSITION_H

enum CellState
{
    empty,
    white,
    black
};

struct Position
{
    int X;
    int Y;
    bool correct() const { return X >= 1 && X <= 8 && Y >= 1 && Y <= 8; }

    Position(){}
    Position(int x, char y): X(x), Y(y) {}

    Position left()  { return Position(X-1, Y); }
    Position right() { return Position(X+1, Y); }
    Position up()    { return Position(X, Y-1); }
    Position down()  { return Position(X, Y+1); }

    Position upleft()    { return Position(X-1, Y-1); }
    Position upright()   { return Position(X+1, Y-1); }
    Position downleft()  { return Position(X-1, Y+1); }
    Position downright() { return Position(X+1, Y+1); }
};

#endif // POSITION_H
