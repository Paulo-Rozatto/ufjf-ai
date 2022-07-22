#include <iostream>
#include <fstream>
#include <list>

#include "puzzle.h"

using namespace std;

bool backtracking(Puzzle *p, list<Puzzle *> *parents, list<Puzzle *> *solution_states, list<int> *solution_moves);
bool bfs(Puzzle *start);
bool dfs(Puzzle *p, int depth);

bool exists(Puzzle *p, list<Puzzle *> *s);
void showSolution(ostream &out, list<Puzzle *> *solution_states, list<int> *solution_moves);
void freeList(list<Puzzle *> *l);

bool backtracking(Puzzle *p, list<Puzzle *> *parents, list<Puzzle *> *solution_states, list<int> *solution_moves)
{
    Puzzle *child;
    bool flag = false;
    parents->push_back(p);

    if (p->checkWin())
        return true;

    child = new Puzzle(p->getN());

    for (int i = 0; i < p->getSize(); i++)
    {
        child->copy(p);

        if (child->move(i))
        {
            if (exists(child, parents))
                continue;
            if (backtracking(child, parents, solution_states, solution_moves))
            {
                solution_states->push_front(child);
                solution_moves->push_front(i);
                return true;
            }
        }
    }
    delete child;
    parents->pop_back();

    return false;
}

bool bfs(Puzzle *start)
{
    list<Puzzle *> queue, closeds;
    Puzzle *p, *child;
    bool win = false;

    p = new Puzzle(start->getN());
    p->copy(start);

    queue.push_back(p);
    int cont = 0;

    while (queue.size() > 0)
    {
        cont++;
        p = queue.front();
        queue.pop_front();

        if (p->checkWin())
        {
            cout << "Solution: ";
            p->show(cout);
            win = true;
            break;
        }

        for (int i = 0; i < p->getSize(); i++)
        {
            child = new Puzzle(p->getN());
            child->copy(p);

            if (child->move(i))
            {
                if (exists(child, &closeds))
                {
                    delete child;
                    continue;
                }
                queue.push_back(child);
            }
            else
                delete child;
        }

        closeds.push_back(p);
    }

    freeList(&queue);
    freeList(&closeds);

    return win;
}

bool dfs(Puzzle *p, int depth)
{
    Puzzle *child;

    if (depth == 0)
        return false;

    if (p->checkWin())
    {
        p->show(cout);
        return true;
    }

    child = new Puzzle(p->getN());
    for (int i = 0; i < p->getSize(); i++)
    {
        child->copy(p);
        child->move(i);
        if (dfs(child, depth - 1))
        {
            delete child;
            return true;
        }
    }

    return false;
}

bool exists(Puzzle *p, list<Puzzle *> *s)
{
    for (std::list<Puzzle *>::iterator it = s->begin(); it != s->end(); ++it)
    {
        if ((*it)->equals(p))
            return true;
    }

    return false;
}

void showSolution(ostream &out, list<Puzzle *> *solution_states, list<int> *solution_moves)
{
    std::list<Puzzle *>::iterator it = solution_states->begin();
    std::list<int>::iterator it2 = solution_moves->begin();

    for (it; it != solution_states->end(); ++it)
    {
        out << "Move: " << *it2 << endl;
        (*it)->show(out);
        it2++;
    }
}

void freeList(list<Puzzle *> *l)
{
    for (std::list<Puzzle *>::iterator it = l->begin(); it != l->end(); ++it)
        delete (*it);
}