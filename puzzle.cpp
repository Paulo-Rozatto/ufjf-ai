#include "puzzle.h"

int Puzzle::id_count = 1;

Puzzle::Puzzle(int n)
{
    this->id = id_count++;
    this->n = n;
    this->size = 2 * n + 1;
    puz = new char[this->size];
    this->space_idx = -1;
}

Puzzle::~Puzzle()
{
    delete[] puz;
}

bool Puzzle::move(int idx)
{
    int distance = idx - space_idx;
    if (distance < 0)
        distance *= -1;

    if (distance > 0 && distance <= this->n)
    {
        this->puz[space_idx] = this->puz[idx];
        this->puz[idx] = '-';
        space_idx = idx;
        return true;
    }

    return false;
}

void Puzzle::fill(std::istream &in)
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
        {
            space_idx = i;
            countSpace++;
        }
    }

    if (countBlue != n)
        std::cout << "Error: blues should be " << n << ", they are " << countBlue << std::endl;

    if (countWhite != n)
        std::cout << "Error: whites should be " << n << ", they are " << countWhite << std::endl;

    if (countSpace != 1)
        std::cout << "Error: spaces should be 1, they are " << countSpace << std::endl;
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

void Puzzle::show(std::ostream& out)
{
    for (int i = 0; i < this->size; i++)
        out << puz[i] << " ";
    out << std::endl;
}

int Puzzle::getSize()
{
    return this->size;
}

char *Puzzle::getPuz()
{
    return puz;
}

void Puzzle::copy(Puzzle *p)
{
    char *puz = p->getPuz();

    this->space_idx = p->space_idx;

    for (int i = 0; i < this->size; i++)
        this->puz[i] = puz[i];
}

bool Puzzle::equals(Puzzle *p)
{
     char *puz = p->getPuz();

    for (int i = 0; i < this->size; i++)
    {
        if (this->puz[i] != puz[i])
            return false;
    }
    return true;
}