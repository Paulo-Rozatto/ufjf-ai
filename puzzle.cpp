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

void Puzzle::fill(istream &in)
{
    int countBlue = 0, countWhite = 0, countSpace = 0;

    for (int i = 0; i < this->size; i++)
    {
        in >> puz[i];

        if (puz[i] == blue)
            countBlue++;
        else if (puz[i] == white)
            countWhite++;
        else if (puz[i] == '-')
            countSpace++;
    }

    if (countBlue != n)
        cout << "Error: blues should be " << n << ", they are " << countBlue << endl;

    if (countWhite != n)
        cout << "Error: whites should be " << n << ", they are " << countWhite << endl;

    if (countSpace != 1)
        cout << "Error: spaces should be 1, they are " << countSpace << endl;
}

void Puzzle::show()
{
    for (int i = 0; i < this->size; i++)
        cout << puz[i] << " ";
    cout << endl;
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