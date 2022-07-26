#include "puzzle.h"

int Puzzle::n = 0;
int Puzzle::size = 0;
int Puzzle::id_count = 0;

Puzzle::Puzzle()
{
    puz = new char[Puzzle::n];
    this->id = ++Puzzle::id_count;
    this->parent_id = -1;
    this->space_idx = -1;
    this->cost = 0;
}

Puzzle::~Puzzle()
{
    delete[] puz;
}

void Puzzle::fill(std::istream &in)
{
    int countBlue = 0, countWhite = 0, countSpace = 0;

    for (int i = 0; i < Puzzle::size; i++)
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

    whiteLeft = n - this->countWhite();

    if (countBlue != n)
        std::cout << "Error: blues should be " << n << ", they are " << countBlue << std::endl;

    if (countWhite != n)
        std::cout << "Error: whites should be " << n << ", they are " << countWhite << std::endl;

    if (countSpace != 1)
        std::cout << "Error: spaces should be 1, they are " << countSpace << std::endl;
}

bool Puzzle::move(int idx)
{
    int distance = abs(idx - space_idx);

    if (distance > 0 && distance <= this->n)
    {
        this->puz[space_idx] = this->puz[idx];
        this->puz[idx] = '-';
        space_idx = idx;
        whiteLeft = n - this->countWhite();
        return true;
    }

    return false;
}

bool Puzzle::checkWin()
{
    return whiteLeft == 0;
}

// Heuristca vai ser o numero de brancas que ainda faltam ir para a esquerda de azuis
int Puzzle::heuristic()
{
    return whiteLeft;
}

int Puzzle::objective() {
    return whiteLeft + cost;
}

// Conta numero de brancas a direita de azuis
int Puzzle::countWhite()
{
    int countWhite = 0;

    for (int i = 0; i < this->size; i++)
    {
        if (puz[i] == white)
            countWhite++;
        else if (puz[i] == blue)
            break;
    }

    return countWhite;
}

void Puzzle::possibleRange(int *start, int *end)
{
    *start = space_idx - Puzzle::n;
    *end = space_idx + Puzzle::n;

    if (*start < 0)
        *start = 0;
    if (*end >= Puzzle::size)
        *end = Puzzle::size;
}

void Puzzle::show(std::ostream &out)
{
    for (int i = 0; i < this->size; i++)
        out << puz[i] << " ";
    out << std::endl;
}

bool Puzzle::equals(Puzzle *p)
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->puz[i] != p->puz[i])
            return false;
    }
    return true;
}

Puzzle *Puzzle::makeChildCopy()
{
    Puzzle *p = new Puzzle();

    p->parent_id = this->id;
    p->space_idx = this->space_idx;
    p->cost = this->cost;
    p->whiteLeft = this->whiteLeft;

    for (int i = 0; i < Puzzle::size; i++)
        p->puz[i] = this->puz[i];

    return p;
}

void Puzzle::clone(Puzzle *p)
{
    this->id = p->id;
    this->parent_id = p->parent_id;
    this->space_idx = p->space_idx;
    this->whiteLeft = p->whiteLeft;
    this->cost = p->cost;

    for (int i = 0; i < Puzzle::size; i++)
        this->puz[i] = p->puz[i];
}