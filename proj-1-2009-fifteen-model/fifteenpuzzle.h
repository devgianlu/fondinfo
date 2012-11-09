/**
 * Example used in programming courses at University of Parma, IT.
 * Author: Michele Tomaiuolo - <tomamic@ce.unipr.it> - 2009
 *
 * This software is free: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License, version 3 or
 * later. See <http://www.gnu.org/licenses/>.
 */

#ifndef FIFTEENPUZZLE_H
#define FIFTEENPUZZLE_H

#include <iostream>
#include <vector>
#include <complex>

using namespace std;

class FifteenPuzzle
{
public:
    typedef complex<int> Coord;
    FifteenPuzzle(int rows, int columns);
    virtual int getColumns() const;
    virtual int getRows() const;
    virtual void init();
    virtual void shuffle();
    virtual void move(char symbol);
    virtual void move(Coord pos);
    virtual char get(Coord pos) const;
    virtual bool isSolved() const;
    virtual void write(ostream& out) const;

    static const char FIRST_SYMBOL = 'A';
    static const char BLANK_SYMBOL = ' ';
    static const char OUT_OF_BOUNDS = '!';

protected:
    virtual void moveBlank(Coord delta);
    virtual void set(Coord pos, char value);

    int columns;
    int rows;

    vector<char> board;
    Coord blank;
    Coord moved;
};

//std::ostream& operator<<(ostream& out, FifteenPuzzle& puzzle);

#endif // FIFTEENPUZZLE_H