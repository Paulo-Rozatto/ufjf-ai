#ifndef PUZZLE_UTIL_H
#define PUZZLE_UTIL_H

#include <list>
#include "puzzle.h"
#include "queue.h"

using namespace std;

struct CmpObjective
{
    bool operator()(const Puzzle *p1, const Puzzle *p2) const
    {
        return (p1->whiteLeft + p1->cost) > (p2->whiteLeft + p2->cost);
    }
};

struct CmpHeuristc
{
    bool operator()(const Puzzle *p1, const Puzzle *p2) const
    {
        return p1->whiteLeft > p2->whiteLeft;
    }
};

bool exists(Puzzle *p, list<Puzzle *> *s)
{
    for (std::list<Puzzle *>::iterator it = s->begin(); it != s->end(); ++it)
    {
        if ((*it)->equals(p))
            return true;
    }

    return false;
}

bool exists(Puzzle *p, MyQueue<Puzzle *, vector<Puzzle *>, CmpHeuristc> *s)
{
    for (MyQueue<Puzzle *, vector<Puzzle *>, CmpHeuristc>::const_iterator it = s->begin(); it != s->end(); ++it)
    {
        if ((*it)->equals(p))
            return true;
    }

    return false;
}

bool exists(Puzzle *p, MyQueue<Puzzle *, vector<Puzzle *>, CmpObjective> *s)
{
    for (MyQueue<Puzzle *, vector<Puzzle *>, CmpObjective>::const_iterator it = s->begin(); it != s->end(); ++it)
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

void freeHeap(MyQueue<Puzzle *, vector<Puzzle *>, CmpHeuristc> *s)
{
    for (MyQueue<Puzzle *, vector<Puzzle *>, CmpHeuristc>::const_iterator it = s->begin(); it != s->end(); ++it)
        delete *it;
}

void freeHeap(MyQueue<Puzzle *, vector<Puzzle *>, CmpObjective> *s)
{
    for (MyQueue<Puzzle *, vector<Puzzle *>, CmpObjective>::const_iterator it = s->begin(); it != s->end(); ++it)
        delete *it;
}

#endif