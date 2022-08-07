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

void buildPath(list<Puzzle *> *closed, list<Puzzle *> *path)
{
    Puzzle *p = closed->back();
    closed->pop_back();

    path->push_front(p);

    for (std::list<Puzzle *>::reverse_iterator it = closed->rbegin(); it != closed->rend(); ++it)
    {
        if (p->parent_id == -1)
            break;
        if (p->parent_id == (*it)->id)
        {
            p = *it;
            path->push_front(p);
            closed->erase(next(it).base());
            --it;
        }
    }
}

void freeList(list<Puzzle *> *s)
{
    for (std::list<Puzzle *>::iterator it = s->begin(); it != s->end(); ++it)
        delete *it;
    s->clear();
}

#endif