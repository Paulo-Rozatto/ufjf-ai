#ifndef PUZZLE_UTIL_H
#define PUZZLE_UTIL_H

#include <list>
#include "puzzle.h"

using namespace std;

bool exists(Puzzle *p, list<Puzzle *> *s)
{
    for (std::list<Puzzle *>::iterator it = s->begin(); it != s->end(); ++it)
    {
        if ((*it)->equals(p))
            return true;
    }

    return false;
}

void showPath(list<Puzzle *> *path)
{
    for (std::list<Puzzle *>::iterator it = path->begin(); it != path->end(); ++it)
        (*it)->show(cout);
}

#endif