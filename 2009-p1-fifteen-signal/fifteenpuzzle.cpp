/**
 * Example used in programming courses at University of Parma, IT.
 * Author: Michele Tomaiuolo - <tomamic@ce.unipr.it> - 2009
 *
 * This software is free: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License, version 3 or
 * later. See <http://www.gnu.org/licenses/>.
 */

#include "fifteenpuzzle.h"

#include <cstdlib>
#include <algorithm>

const int FifteenPuzzle::DY[] = { -1,  0, +1,  0}; // N, E, S, W
const int FifteenPuzzle::DX[] = {  0, +1,  0, -1}; // N, E, S, W

FifteenPuzzle::FifteenPuzzle(int rows, int columns)
{
    if (rows < 2) rows = 2;
    if (columns < 2) columns = 2;
    this->rows = rows;
    this->columns = columns;
    size = columns * rows;
    board.assign(size, BLANK_SYMBOL);

    init();
    shuffle();
}

int FifteenPuzzle::getColumns() const
{
    return columns;
}

int FifteenPuzzle::getRows() const
{
    return rows;
}

void FifteenPuzzle::init()
{
    // put ordered symbols in each cell (ltr, ttb)
    int value = FIRST_SYMBOL;
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < columns; ++x) {
            set(y, x, value);
            ++value;
        }
    }
    // put blank in the last cell
    blankY = rows - 1;
    blankX = columns - 1;
    set(blankY, blankX, BLANK_SYMBOL);
}

void FifteenPuzzle::shuffle()
{
    do {
        // generate SIZE^2 random directions
        // for a random walk of the blank cell
        for (int i = 0; i < size * size; ++i) {
            int direction = rand() % DIRECTIONS;

            // consider the cell adjacent to the
            // blank cell, in the current direction
            int nextY = blankY + DY[direction];
            int nextX = blankX + DX[direction];
            // if it is inside the board, then move the blank
            if (0 <= nextY && nextY < rows
                    && 0 <= nextX && nextX < columns) {
                moveBlank(direction, true); // silent, no signals emitted
            }
        }
    } while (isSolved());
}

void FifteenPuzzle::move(char symbol)
{
    bool found = false;
    // for each direction, while symbol not yet found...
    for (int direction = 0; direction < DIRECTIONS
         && !found; ++direction) {
        // consider the cell adjacent to the
        // blank cell, in the current direction
        int nextY = blankY + DY[direction];
        int nextX = blankX + DX[direction];
        // if the symbol to move is here...
        if (get(nextY, nextX) == symbol) {
            found = true;
            // move blank this way!
            moveBlank(direction);
        }
    }
}

void FifteenPuzzle::move(int y, int x)
{
    char symbol = get(y, x);
    if (symbol != OUT_OF_BOUNDS) {
        move(symbol);
    }
}

char FifteenPuzzle::get(int y, int x) const
{
    int value = OUT_OF_BOUNDS;
    if (0 <= y && y < rows && 0 <= x && x < columns) {
        value = board[y * columns + x];
    }
    return value;
}

void FifteenPuzzle::set(int y, int x, int value)
{
    board[y * columns + x] = value;
}

void FifteenPuzzle::moveBlank(int direction, bool silent)
{
    int oldY = blankY;
    int oldX = blankX;
    blankY += DY[direction];
    blankX += DX[direction];
    set(oldY, oldX, get(blankY, blankX));
    set(blankY, blankX, BLANK_SYMBOL);
    // while shuffling, no signals are emitted
    if (! silent) {
        emit blankMoved(blankY, blankX, oldY, oldX);
    }
}

bool FifteenPuzzle::isSolved() const
{
    bool correct = true;
    char expected = FIRST_SYMBOL;
    for (int y = 0; y < rows && correct; ++y) {
        for (int x = 0; x < columns && correct; ++x) {
            char value = get(y, x);
            // if the cell has the wrong symbol...
            // puzzle is not yet solved!
            if (value != expected && value != BLANK_SYMBOL) {
                correct = false;
            }
            ++expected;
        }
    }
    return correct;
}

void FifteenPuzzle::write(std::ostream& out) const
{
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < columns; ++x) {
            out << get(y, x);
        }
        out << endl;
    }
    out << endl;
}

//std::ostream& operator<<(std::ostream& out, FifteenPuzzle& puzzle)
//{
//    puzzle.write(out);
//    return out;
//}
