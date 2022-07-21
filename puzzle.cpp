#include "puzzle.h"

Puzzle::Puzzle(int n)
{
    this->n = n;
    this->size = 2 * n + 1;
    puz = new char[this->size];
}

Puzzle::~Puzzle()
{
    delete[] puz;
}

bool Puzzle::checkWin()
{
    bool flag = false;
    int countWhite = 0;

    for (int i = 0; i < 2 * n + 1; i++)
    {
        if (puz[i] == white)
            countWhite++;
        else if (puz[i] == blue)
            break;
    }

    return (countWhite == n);
}